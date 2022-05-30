#pragma once
#include"Room.h"

class RoomBoss : public Room
{

private:

	// init room objects
	virtual void initObjects();

	// init room enemies
	virtual void initEnemies();

public:

	// default constructor with room position
	RoomBoss(sf::Vector2f pos);
};