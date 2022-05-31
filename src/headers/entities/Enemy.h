#pragma once
#include"Entity.h"
#include"../../headers/tools/DifferentTools.h"

enum class MoveAxis
{
	X,
	Y
};

class Enemy : public Entity
{
private:

	//------PRIVATE VARS------

	MoveAxis move_axis;			// on which coord axis enemy will follow player

	int time_change;			// how much time needs to change movement behaviour
	int time_passed;			// how much time passed since last behaviour change

	bool move_x;				// behaviour logic X axis
	bool move_y;				// behaviour logic Y axis

	sf::Vector2f player_pos;	// tracked player's position

public:

	// default constructor
	Enemy();

	//------METHODS------

	// update player position
	void track(sf::Vector2f pos);

	// following the player
	void followPlayer();
};