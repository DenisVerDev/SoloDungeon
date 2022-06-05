#pragma once
#include"Room.h"
#include"../../headers/entities/Demon.h"

class RoomDemon : public Room
{
private:

	// init room objects
	virtual void initObjects();

	// init room enemies
	virtual void initEnemies();

public:

	// default constructor with room position
	RoomDemon(sf::Vector2f pos);
};