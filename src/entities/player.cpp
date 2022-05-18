#include"../../src/headers/entities/Player.h"

//------Constructor definition------

Player::Player() : Entity()
{
	this->texture_rect.left = 0;
	this->texture_rect.top = 0;
	this->texture_rect.width = 50;
	this->texture_rect.height = 37;

	this->body.setTexture(Player::texture);
	this->body.setTextureRect(this->texture_rect);

	this->speed = 0.0004f;
}

//------Methods definition------

void Player::behave()
{
	// checking player's input

	// player's movement
	if (sf::Keyboard::isKeyPressed(GameInput::getKeyByAction(PlayerAction::MoveUp)))
	{
		this->body.move(0.f, -this->speed);
	}
	else if (sf::Keyboard::isKeyPressed(GameInput::getKeyByAction(PlayerAction::MoveDown)))
	{
		this->body.move(0.f, this->speed);
	}

	if (sf::Keyboard::isKeyPressed(GameInput::getKeyByAction(PlayerAction::MoveRight)))
	{
		this->body.move(this->speed, 0.f);
		this->turn_type = TurnType::Right;
	}
	else if (sf::Keyboard::isKeyPressed(GameInput::getKeyByAction(PlayerAction::MoveLeft)))
	{
		this->body.move(-this->speed, 0.f);
		this->turn_type = TurnType::Left;
	}

	turnHandle();
}

void Player::turnHandle()
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
}

void Player::draw(sf::RenderTarget& target)
{
	target.draw(this->body);
}

void Player::loadTexture()
{
	this->texture.loadFromFile(GameResources::enities_texture + "adventurer-v1.5-Sheet.png");
}
