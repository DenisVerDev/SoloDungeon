#include"../../src/headers/entities/Demon.h"

Demon::Demon() : Enemy()
{
	// texture_rect settings
	this->texture_rect.left = 369;
	this->texture_rect.top = 329;
	this->texture_rect.width = 16;
	this->texture_rect.height = 24;

	this->body.setOrigin(sf::Vector2f(this->texture_rect.width / 2.f, this->texture_rect.height / 2.f));

	// individual undead settings
	this->base_speed = 0.2f;
	this->effect_speed = 0.3f;
	this->speed = this->base_speed;

	this->damage_range = 10.f;

	this->health = 1;
	this->damage = 1;

	// animation initialization
	this->initAnim();
}

void Demon::initAnim()
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
	move_anim.init(4, time, sf::Vector2i(433, 329), true);
}