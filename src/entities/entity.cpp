#include"../../src/headers/entities/Entity.h"

//------Constructor definition------

Entity::Entity()
{
	this->turn_type = TurnType::Right;

	this->turnHandle();
	this->resetMove();
}

//------Methods definition------

void Entity::update()
{
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
	this->move_up = false;
	this->move_down = false;
	this->move_right = false;
	this->move_left = false;
	this->entity_state = EntityState::Stand;
}

void Entity::turnHandle()
{
	if (this->move_right != this->move_left)
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
