#include"../../src/headers/entities/Player.h"

//------Constructor/Destructor definition------

Player::Player() : Entity()
{
	// texture_rect settings
	this->texture_rect.left = 128;
	this->texture_rect.top = 69;
	this->texture_rect.width = 16;
	this->texture_rect.height = 28;

	this->body.setOrigin(sf::Vector2f(this->texture_rect.width / 2.f, this->texture_rect.height / 2.f));

	// sword initialization
	this->sword = new Sword();

	// individual player's settings
	this->base_speed = 0.3f;
	this->effect_speed = this->base_speed;
	this->speed = this->base_speed;

	this->damage_range = this->sword->getRange();

	this->max_health = 6;
	this->health = this->max_health;
	this->damage = this->sword->getDamage();

	// camera settings
	this->camera_speed = this->speed * 1.5f;
	this->camera_radius = 85.f;

	this->isOutOfRadius = false;

	// animation initialization
	this->initAnim();

	// init sound
	AudioManager::initSound(this->sword_attack, SFXType::SwordHit);
}

Player::~Player()
{
	delete this->sword;
	this->sword = nullptr;
}

//------Methods definition------

void Player::initAnim()
{
	std::vector<unsigned int> time;
	for (int i = 0; i < 4; i++)
	{
		time.push_back(Animation::ATime * 0.048);
	}
	stand_anim.init(4, time, sf::Vector2i(this->texture_rect.left, this->texture_rect.top), true);

	time.clear();
	for (int i = 0; i < 4; i++)
	{
		time.push_back(Animation::ATime * 0.048);
	}
	move_anim.init(4, time, sf::Vector2i(192, 69), true);
}

void Player::update()
{
	EntityState previous_state = this->entity_state;

	this->effectProcessing();

	if (this->isAlive == true)
	{

		if (this->entity_state != EntityState::Hitted && this->entity_state != EntityState::Death)
		{

			if (sf::Keyboard::isKeyPressed(GameInput::getKeyByAction(PlayerAction::MoveUp)))
			{
				this->move_up = true;
				this->entity_state = EntityState::Move;
			}

			if (sf::Keyboard::isKeyPressed(GameInput::getKeyByAction(PlayerAction::MoveDown)))
			{
				this->move_down = true;
				this->entity_state = EntityState::Move;
			}

			if (sf::Keyboard::isKeyPressed(GameInput::getKeyByAction(PlayerAction::MoveRight)))
			{
				this->move_right = true;
				this->entity_state = EntityState::Move;
			}

			if (sf::Keyboard::isKeyPressed(GameInput::getKeyByAction(PlayerAction::MoveLeft)))
			{
				this->move_left = true;
				this->entity_state = EntityState::Move;
			}

			// player attack check
			if (GameCycle::mouse_data.getIsMouseButtonPressed(GameInput::getButtonByAction(PlayerAction::Attack)))
			{
				this->sword->startBaseAttack();
			}
		}

		this->turnHandle();

		// player and camera movement
		this->move();
		this->cameraMove();

		// update sword state
		this->sword->update(this->getTurnType());

		// animation update
		this->updateAnim(previous_state);
	}
}

void Player::attack(Entity& entity)
{
	// play sound
	this->sword_attack.play();

	// check if entity is in our attack range distance

	sf::Vector2f entity_pos = entity.getPosition();

	if (this->turn_type == TurnType::Right)
	{
		// X axis check
		if (this->position.x >= entity_pos.x - this->damage_range && this->position.x <= entity_pos.x)
		{
			// Y axis check
			if (this->position.y >= entity_pos.y - this->damage_range && this->position.y <= entity_pos.y + this->damage_range)
			{
				// hit entity
				entity.getHit(*this);
			}
		}
	}
	else
	{
		//  X check
		if (this->position.x <= entity_pos.x + this->damage_range && this->position.x >= entity_pos.x)
		{
			// Y axis check
			if (this->position.y >= entity_pos.y - this->damage_range && this->position.y <= entity_pos.y + this->damage_range)
			{
				// hit entity
				entity.getHit(*this);
			}
		}
	}
}

void Player::cameraMove()
{
	sf::Vector2f camera = GameRender::rview.getCenter();

	if (this->entity_state == EntityState::Move || this->entity_state == EntityState::Hitted || this->entity_state == EntityState::Death)
	{
		// X axis
		if (this->position.x < camera.x - this->camera_radius)
		{
			GameRender::rview.move(-this->speed, 0.f);
			this->isOutOfRadius = true;
		}
		if (this->position.x > camera.x + this->camera_radius)
		{
			GameRender::rview.move(this->speed, 0.f);
			this->isOutOfRadius = true;
		}

		// Y axis
		if (this->position.y < camera.y - this->camera_radius)
		{
			GameRender::rview.move(0.f, -this->speed);
			this->isOutOfRadius = true;
		}
		if (this->position.y > camera.y + this->camera_radius)
		{
			GameRender::rview.move(0.f, this->speed);
			this->isOutOfRadius = true;
		}
	}
	else if (this->entity_state == EntityState::Stand || this->entity_state == EntityState::Hitted || this->entity_state == EntityState::Death)
	{
		// X axis
		if (this->position.x < camera.x && this->isOutOfRadius == true)
		{
			float distance = camera.x - this->position.x;
			if(std::abs(distance) >= this->camera_speed) GameRender::rview.move(-this->camera_speed, 0.f);
			else GameRender::rview.move(-distance, 0.f);
		}

		if (this->position.x > camera.x && this->isOutOfRadius == true)
		{
			float distance = this->position.x - camera.x;
			if (std::abs(distance) >= this->camera_speed) GameRender::rview.move(this->camera_speed, 0.f);
			else GameRender::rview.move(distance, 0.f);
		}

		// Y axis
		if (this->position.y < camera.y && this->isOutOfRadius == true)
		{
			float distance = camera.y - this->position.y;
			if (std::abs(distance) >= this->camera_speed) GameRender::rview.move(0.f, -this->camera_speed);
			else GameRender::rview.move(0.f, -distance);
		}

		if (this->position.y > camera.y && this->isOutOfRadius == true)
		{
			float distance = this->position.y - camera.y;
			if (std::abs(distance) >= this->camera_speed) GameRender::rview.move(0.f, this->camera_speed);
			else GameRender::rview.move(0.f, distance);
		}

		if (this->position == camera) this->isOutOfRadius = false;
	}
}

void Player::draw(sf::RenderTarget& target)
{
	target.draw(this->body);
	if(this->entity_state != EntityState::Death) this->sword->draw(target);
}

void Player::setTexture(sf::Texture& texture)
{
	this->body.setTexture(texture);
	this->body.setTextureRect(this->texture_rect);
	this->sword->setTexture(texture);
}

void Player::setPosition(sf::Vector2f position)
{
	this->position = position;
	this->body.setPosition(this->position);
	this->sword->bind(*this);
}

void Player::initCamera()
{
	GameRender::rview.setCenter(this->position); // setting camera position relative to the player
}

int Player::getMaxHealth()
{
	return this->max_health;
}

bool Player::getAttack()
{
	return this->sword->getAttackFinish();
}