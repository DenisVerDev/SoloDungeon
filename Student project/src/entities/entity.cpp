#include"../../src/headers/entities/Entity.h"

//------Constructor definition------

Entity::Entity()
{
	this->isAlive = true;

	this->effect_duration = 100;
	this->effect_count = 0;

	this->turn_type = TurnType::Right;

	this->turnHandle();
	this->resetMove();

	// init sound
	AudioManager::initSound(this->hitted, SFXType::EntityHitted);
}

//------Methods definition------

void Entity::update()
{
}

void Entity::attack(Entity& entity)
{
	// check if entity is in our attack range distance

	sf::Vector2f entity_pos = entity.getPosition();

	// X axis check
	if (this->position.x >= entity_pos.x - this->damage_range && this->position.x <= entity_pos.x + this->damage_range)
	{
		// Y axis check
		if (this->position.y >= entity_pos.y - this->damage_range && this->position.y <= entity_pos.y + this->damage_range)
		{
			// flee after the attack to let the player some space
			
			// X axis
			if (this->turn_type == TurnType::Right)
			{
				this->move_left = true;
				this->move_right = false;
			}
			else
			{
				this->move_right = true;
				this->move_left = false;
			}

			// Y axis
			if (this->position.y >= entity_pos.y - this->damage_range && entity_pos.y < this->position.y)
			{
				this->move_up = true;
				this->move_down = false;
			}
			else if (entity_pos.y <= this->position.y + this->damage_range && entity_pos.y > this->position.y)
			{
				this->move_down = true;
				this->move_up = false;
			}

			// change state
			this->entity_state = EntityState::Flee;

			// hit entity
			entity.getHit(*this);
		}
	}
}

void Entity::getHit(Entity& attacker)
{
	if (this->isAlive == true)
	{
		// play sound
		this->hitted.play();

		// check in which side entity should repulse
		TurnType attack_turn = attacker.getTurnType();

		sf::Vector2f attack_pos = attacker.getPosition();
		float attack_range = attacker.getAttackRange();

		// X axis
		if (attack_turn == TurnType::Right)
		{
			this->move_right = true;
			this->move_left = false;
		}
		else
		{
			this->move_left = true;
			this->move_right = false;
		}

		// Y axis
		if (attack_pos.y >= this->position.y - attack_range && attack_pos.y < this->position.y)
		{
			this->move_down = true;
			this->move_up = false;
		}
		else if (attack_pos.y <= this->position.y + attack_range && attack_pos.y > this->position.y)
		{
			this->move_up = true;
			this->move_down = false;
		}

		// updating stats and state
		if (this->health > 0)
		{
			this->health -= attacker.getAttackDamage();
			this->entity_state = EntityState::Hitted;
			this->body.setColor(sf::Color::Red);		 // to see what entity was hitted
		}

		if (this->health <= 0)
		{
			if (this->turn_type == TurnType::Right) this->body.rotate(90.f);
			else this->body.rotate(-90.f);

			this->entity_state = EntityState::Death;
			this->body.setColor(sf::Color(105, 105, 105));
		}
	}
}

void Entity::effectProcessing()
{
	if (this->isAlive == true)
	{
		if (this->entity_state != EntityState::Hitted && this->entity_state != EntityState::Death && this->entity_state != EntityState::Flee)
		{
			if (this->effect_count == 0)	this->resetMove();
		}
		else if (this->entity_state == EntityState::Hitted || this->entity_state == EntityState::Death || this->entity_state == EntityState::Flee)
		{
			this->speed = this->effect_speed;

			if (this->effect_count < this->effect_duration) this->effect_count++;
			else
			{
				if (this->entity_state != EntityState::Death)
				{
					this->effect_count = 0;
					this->resetMove();
				}
				else this->isAlive = false;
			}
		}
	}
}

void Entity::move()
{
	sf::Vector2f pos;

	if (this->move_up && this->move_down == false)
	{
		pos.x = this->position.x;
		pos.y = this->position.y - this->speed;
		this->setPosition(pos);
	}
	else if (this->move_down && this->move_up == false)
	{
		pos.x = this->position.x;
		pos.y = this->position.y + this->speed;
		this->setPosition(pos);
	}

	if (this->move_right && this->move_left == false)
	{
		pos.x = this->position.x + this->speed;
		pos.y = this->position.y;
		this->setPosition(pos);
	}
	else if (this->move_left && this->move_right == false)
	{
		pos.x = this->position.x - this->speed;
		pos.y = this->position.y;
		this->setPosition(pos);
	}
}

void Entity::resetMove()
{
	this->body.setColor(sf::Color(255, 255, 255)); // reset color
	this->speed = this->base_speed;
	this->move_up = false;
	this->move_down = false;
	this->move_right = false;
	this->move_left = false;
	this->entity_state = EntityState::Stand;
}

void Entity::turnHandle()
{
	if (this->move_right != this->move_left && this->entity_state != EntityState::Hitted)
	{
		if (this->turn_type == TurnType::Left && this->move_right)
		{
			this->turn_type = TurnType::Right;
			this->hasTurned = true;
		}
		else if (this->turn_type == TurnType::Right && this->move_left)
		{
			this->turn_type = TurnType::Left;
			this->hasTurned = true;
		}

		if (this->hasTurned == true)
		{
			switch (this->turn_type)
			{
				case TurnType::Right:
					this->body.setScale(1, 1);
					break;

				case TurnType::Left:
					this->body.setScale(-1, 1);
					break;
			}

			this->hasTurned = false;
		}

	}
}

void Entity::updateAnim(EntityState previous_state)
{
	switch (this->entity_state)
	{
		case EntityState::Stand:
			if (previous_state != this->entity_state) this->stand_anim.reset();
			this->stand_anim.update(this->body, this->texture_rect);
			break;

		case EntityState::Move:
			if (previous_state != this->entity_state) this->move_anim.reset();
			this->move_anim.update(this->body, this->texture_rect);
			break;

		default:break;
	}
}

void Entity::initAnim()
{

}

void Entity::draw(sf::RenderTarget& target)
{
	target.draw(this->body);
}

void Entity::collisionResponse(bool left, bool right, bool top, bool bottom)
{
	if (left == true) this->setPosition(sf::Vector2f(this->position.x + this->speed, this->position.y));
	if (right == true) this->setPosition(sf::Vector2f(this->position.x - this->speed, this->position.y));
	if (top == true) this->setPosition(sf::Vector2f(this->position.x, this->position.y + this->speed));
	if (bottom == true) this->setPosition(sf::Vector2f(this->position.x, this->position.y - this->speed));
}

void Entity::setTexture(sf::Texture& texture)
{
	this->body.setTexture(texture);
	this->body.setTextureRect(this->texture_rect);
}

void Entity::setPosition(sf::Vector2f position)
{
	this->position = position;
	this->body.setPosition(this->position);
}

//------Getters definition------

sf::Vector2f Entity::getPosition()
{
	return this->position;
}

sf::Vector2f Entity::getSize()
{
	return sf::Vector2f(this->texture_rect.width, this->texture_rect.height);
}

TurnType Entity::getTurnType()
{
	return this->turn_type;
}

EntityState Entity::getState()
{
	return this->entity_state;
}

sf::IntRect Entity::getCollision()
{
	sf::IntRect collision;
	sf::Vector2f size = this->getSize();

	// every entity has it's origin set to texture center
	collision.left = this->position.x;
	collision.top = this->position.y + size.y/2.5;
	collision.width = size.x / 2;
	collision.height = size.y / 2 - size.y / 2.5;

	return collision;
}

float Entity::getAttackRange()
{
	return this->damage_range;
}

int Entity::getAttackDamage()
{
	return this->damage;
}

int Entity::getHealth()
{
	return this->health;
}

bool Entity::getIsAlive()
{
	return this->isAlive;
}

bool Entity::getAttack()
{
	return false;
}
