#include"../../src/headers/entities/Slime.h"

Slime::Slime() : Enemy()
{
	// texture_rect settings
	this->texture_rect.left = 433;
	this->texture_rect.top = 113;
	this->texture_rect.width = 16;
	this->texture_rect.height = 16;

	this->body.setOrigin(sf::Vector2f(this->texture_rect.width / 2.f, this->texture_rect.height / 2.f));

	// individual undead settings
	this->speed = 0.1f;
	this->damage_range = 80.f;

	this->health = 1;
	this->damage = 2;

	// animation initialization
	this->initAnim();
}

void Slime::initAnim()
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
		time.push_back(Animation::ATime * 0.06);
	}
	move_anim.init(4, time, sf::Vector2i(this->texture_rect.left, this->texture_rect.top), true);
}

void Slime::update()
{
	EntityState previous_state = this->entity_state;
	this->resetMove();

	this->followPlayer();

	this->turnHandle();
	this->move();

	// animation update
	this->updateAnim(previous_state);
}