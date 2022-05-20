#include"../../src/headers/entities/Player.h"

//------Constructor definition------

Player::Player() : Entity()
{
	// texture_rect settings
	this->texture_rect.left = 0;
	this->texture_rect.top = 0;
	this->texture_rect.width = 50;
	this->texture_rect.height = 37;

	// sprite settings
	this->body.setTexture(Player::texture);
	this->body.setTextureRect(this->texture_rect);
	this->body.setOrigin(sf::Vector2f(this->texture_rect.width / 2.f, this->texture_rect.height / 2.f));

	// individual player's settings
	this->speed = 0.0004f;

	// camera settings
	this->camera_speed = this->speed * 1.5f;
	this->camera_radius = 85.f;

	this->isOutOfRadius = false;

	// animation initialization
	this->initAnim();
}

//------Methods definition------

void Player::initAnim()
{
	std::vector<unsigned int> time;
	for (int i = 0; i < 4; i++)
	{
		time.push_back(Animation::ATime * 4);
	}
	stand_anim.init(4, time, sf::Vector2i(this->texture_rect.left, this->texture_rect.top), true);

	time.clear();
	for (int i = 0; i < 6; i++)
	{
		time.push_back(Animation::ATime * 4);
	}
	move_anim.init(6, time, sf::Vector2i(this->texture_rect.width, this->texture_rect.height), true);
}

void Player::update()
{

	// player's movement

	EntityState previous_state = this->entity_state;
	this->resetMove();

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

	this->turnHandle();

	// player and camera movement
	this->move();
	this->cameraMove();

	// animation update
	this->updateAnim(previous_state);
}

void Player::updateAnim(EntityState previous_state)
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

void Player::cameraMove()
{
	sf::Vector2f camera = GameRender::rview.getCenter();

	if (this->entity_state == EntityState::Move)
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
	else if (this->entity_state == EntityState::Stand)
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

void Player::loadTexture()
{
	this->texture.loadFromFile(GameResources::enities_texture + "adventurer-v1.5-Sheet.png");
}

void Player::setPosition(sf::Vector2f position, bool update_camera)
{
	this->position = position;
	this->body.setPosition(this->position);

	if(update_camera) GameRender::rview.setCenter(this->position); // setting camera position relative to the player
}
