#pragma once
#include"Room.h"
#include"../../headers/entities/Slime.h"

class RoomSlime : public Room
{
private:

	// init room objects
	virtual void initObjects();

	// init room enemies
	virtual void initEnemies();

public:

	// default constructor with room position
	RoomSlime(sf::Vector2f pos);
};