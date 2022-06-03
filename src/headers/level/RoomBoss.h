#pragma once
#include"Room.h"
#include"../../headers/entities/Undead.h"
#include"../../headers/entities/Orc.h"
#include"../../headers/entities/Slime.h"
#include"../../headers/entities/Demon.h"

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