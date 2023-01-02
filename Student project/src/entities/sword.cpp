#include"../../src/headers/entities/Sword.h"

Sword::Sword()
{
	// base vars initialization
	this->base_angle = 75.f;
	this->up_angle = 0.f;
	this->down_angle = 180.f;
	this->cur_angle = this->base_angle;

	this->rise_up = false;
	this->rise_down = false;

	this->attack = false;
	this->attack_finished = false;

	// characteristics initialization
	this->base_damage = 1;
	this->base_range = 24.f;

	this->attack_speed = 2.4f;

	// graphical components initialization
	this->texure_rect.left = 293;
	this->texure_rect.top = 82;
	this->texure_rect.width = 6;
	this->texure_rect.height = 29;

	this->body.setTextureRect(this->texure_rect);
	this->body.setOrigin(sf::Vector2f(this->texure_rect.width / 2, 21));
	this->body.setRotation(75);
	this->body.setScale(0.9f, 0.9f);
}

//------Methods definition------

void Sword::update(TurnType type)
{
	switch (type)
	{
		case TurnType::Right:
			this->base_angle = 75.f;
			this->up_angle = 0.f;
			if (this->cur_angle > this->down_angle) this->cur_angle = 360.f - this->cur_angle;
			break;

		case TurnType::Left:
			this->base_angle = 285.f;
			this->up_angle = 360.f;
			if(this->cur_angle < this->down_angle) this->cur_angle = 360.f - this->cur_angle;
			break;
	}

	if (this->attack == true) this->attackAnim(type);
}

void Sword::startBaseAttack()
{
	if (this->attack == false)
	{
		this->attack = true;
		this->attack_finished = false;

		this->rise_up = true;
		this->rise_down = false;
	}
}

void Sword::bind(Player& player)
{
	sf::Vector2f pos = player.getPosition();
	sf::Vector2f size = player.getSize();

	switch (player.getTurnType())
	{
		case TurnType::Right:
			this->body.setScale(0.9f, 0.9f);
			this->body.setPosition(sf::Vector2f(pos.x + size.x - 4, pos.y + size.y / 4.f));
			break;

		case TurnType::Left:
			this->body.setScale(-0.9f, 0.9f);
			this->body.setPosition(sf::Vector2f(pos.x - size.x + 4, pos.y + size.y / 4.f));
			break;
	}

	if (this->attack == false) this->body.setRotation(this->base_angle);
}

void Sword::attackAnim(TurnType type)
{
	if (this->cur_angle == this->up_angle)
	{
		this->rise_up = false;
		this->rise_down = true;
	}
	else if (this->cur_angle == this->down_angle)
	{
		this->rise_up = false;
		this->rise_down = false;

		this->attack_finished = true;
	}
	else if (this->cur_angle == this->base_angle && this->rise_up == false && this->rise_down == false)
	{
		this->attack = false;
	}


	switch (type)
	{
		case TurnType::Right:

			if (this->rise_up == true && this->cur_angle > this->up_angle + this->attack_speed) this->cur_angle -= this->attack_speed;
			else if(this->rise_up == true && this->cur_angle > this->up_angle) this->cur_angle = this->up_angle;

			if (this->rise_down == true && this->cur_angle < this->down_angle - this->attack_speed) this->cur_angle += this->attack_speed;
			else if(this->rise_down == true && this->cur_angle < this->down_angle)  this->cur_angle = this->down_angle;
			
			if(this->rise_up == false && this->rise_down == false && this->cur_angle > this->base_angle + this->attack_speed) this->cur_angle -= this->attack_speed;
			else if(this->rise_up == false && this->rise_down == false && this->cur_angle > this->base_angle) this->cur_angle = this->base_angle;

			break;

		case TurnType::Left:

			if (this->rise_up == true && this->cur_angle < this->up_angle - this->attack_speed) this->cur_angle += this->attack_speed;
			else if(this->rise_up == true && this->cur_angle < this->up_angle) this->cur_angle = this->up_angle;

			if (this->rise_down == true && this->cur_angle > this->down_angle + this->attack_speed) this->cur_angle -= this->attack_speed;
			else if(this->rise_down == true && this->cur_angle > this->down_angle) this->cur_angle = this->down_angle;
			
			if (this->rise_up == false && this->rise_down == false && this->cur_angle < this->base_angle  -this->attack_speed) this->cur_angle += this->attack_speed;
			else if(this->rise_up == false && this->rise_down == false && this->cur_angle < this->base_angle) this->cur_angle = this->base_angle;

			break;
	}

	this->body.setRotation(this->cur_angle);
}

void Sword::draw(sf::RenderTarget& target)
{
	target.draw(this->body);
}

void Sword::setTexture(sf::Texture& texture)
{
	this->body.setTexture(texture);
}

//------Getters definition------

int Sword::getDamage()
{
	return this->base_damage;
}

float Sword::getRange()
{
	return this->base_range;
}

sf::Vector2f Sword::getPosition()
{
	return this->body.getPosition();
}

sf::Vector2f Sword::getSize()
{
	return sf::Vector2f(this->texure_rect.width,this->texure_rect.height);
}

bool Sword::getAttackFinish()
{
	if (this->attack_finished == true)
	{
		this->attack_finished = false;
		return true;
	}

	return false;
}

