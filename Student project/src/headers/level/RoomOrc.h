#pragma once
#include"Room.h"
#include"../../headers/entities/Orc.h"

class RoomOrc : public Room
{
private:

	// init room objects
	virtual void initObjects();

	// init room enemies
	virtual void initEnemies();

public:

	// default constructor with room position
	RoomOrc(sf::Vector2f pos);
};