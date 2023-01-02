#include"../../src/headers/entities/Enemy.h"

//------Constructor/Destructor definition------

Enemy::Enemy() : Entity()
{
	this->player = nullptr;

	this->move_axis = (MoveAxis)dt::rand(0, 1);
	this->move_x = dt::rand(0, 1);
	this->move_y = dt::rand(0, 1);

	this->time_change = Animation::ATime * 0.3;
	this->time_passed = 0;
}

Enemy::~Enemy()
{
	this->player = nullptr;
}

//------Methods definition------

void Enemy::track(Entity& player)
{
	if (this->player == nullptr) this->player = &player;
}

void Enemy::update()
{
	EntityState previous_state = this->entity_state;

	this->effectProcessing();

	if (this->isAlive == true)
	{
		if (this->entity_state != EntityState::Flee && this->entity_state != EntityState::Hitted && this->entity_state != EntityState::Death)
		{
			EntityState player_state = this->player->getState();
			if (player_state != EntityState::Hitted && player_state != EntityState::Death)
			{
				this->followPlayer();
				this->attack(*this->player);
			}
		}

		this->turnHandle();
		this->move();

		// animation update
		this->updateAnim(previous_state);
	}
}

void Enemy::followPlayer()
{
	sf::Vector2f player_pos = this->player->getPosition();

	if (this->time_passed >= this->time_change)
	{
		this->move_x = dt::rand(0, 1);
		this->move_y = dt::rand(0, 1);

		this->time_passed = 0;
	}
	else this->time_passed++;

	switch (this->move_axis)
	{

	case MoveAxis::X:

		if (this->position.x < player_pos.x - this->damage_range)
		{
			this->move_right = true;
			this->move_left = false;
			this->entity_state = EntityState::Move;
		}
		else if (this->position.x > player_pos.x + this->damage_range)
		{
			this->move_left = true;
			this->move_right = false;
			this->entity_state = EntityState::Move;
		}

		if (this->position.x >= player_pos.x - this->damage_range && this->position.x <= player_pos.x + this->damage_range)
		{
			if (this->position.y < player_pos.y - this->damage_range || this->position.y > player_pos.y + this->damage_range) this->move_axis = MoveAxis::Y;
		}
		else
		{
			this->move_down = this->move_y;
			this->move_up = !this->move_y;
		}

		break;

	case MoveAxis::Y:

		if (this->position.y < player_pos.y - this->damage_range)
		{
			this->move_down = true;
			this->move_up = false;
			this->entity_state = EntityState::Move;
		}
		else if (this->position.y > player_pos.y + this->damage_range)
		{
			this->move_up = true;
			this->move_down = false;
			this->entity_state = EntityState::Move;
		}

		if (this->position.y >= player_pos.y - this->damage_range && this->position.y <= player_pos.y + this->damage_range)
		{
			if (this->position.x < player_pos.x - this->damage_range || this->position.x > player_pos.x + this->damage_range) this->move_axis = MoveAxis::X;
		}
		else
		{
			this->move_right = this->move_x;
			this->move_left = !this->move_x;
		}

		break;
	}
}
