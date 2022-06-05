#pragma once
#include"Entity.h"
#include"../../headers/tools/DifferentTools.h"

/*-------------------------------------------------------------------------------------------
	Enemy class:
	- basicly entity class modification to fit in encounter behaviour with player
-------------------------------------------------------------------------------------------*/

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

public:

	Entity* player;				// tracked player

	// default constructor
	Enemy();

	// destructor
	~Enemy();

	//------METHODS------

	// start tracking player
	void track(Entity& player);

	// update enemy state
	virtual void update();

	// following the player
	void followPlayer();
};