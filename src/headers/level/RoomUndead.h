#pragma once
#include"Room.h"
#include"../../headers/entities/Undead.h"

class RoomUndead : public Room 
{

private:

	// init room objects
	virtual void initObjects();

	// init room enemies
	virtual void initEnemies();

public:

	// default constructor with room position
	RoomUndead(sf::Vector2f pos);
};