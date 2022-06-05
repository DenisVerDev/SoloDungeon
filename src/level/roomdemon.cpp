#include"../../src/headers/level/RoomDemon.h"

RoomDemon::RoomDemon(sf::Vector2f pos) : Room(pos)
{
	this->room_name = "THE DEMON ROOM";

	// init all room objects and enemies
	this->initObjects();
	this->initEnemies();
}

void RoomDemon::initObjects()
{
	this->buildDefRoom();

	// flag initialization
	sf::Vector2f flag_pos = this->front_walls[3].getPosition();

	Wall flag(WallType::WallFlagRed);
	flag.setPosition(sf::Vector2f(flag_pos.x, flag_pos.y + 4));	// 4 is wall top height

	this->front_walls.push_back(flag);

	// lava walls initialization
	sf::Vector2f liquid_pos = this->front_walls[6].getPosition(); // lava walls position

	Wall lava_wall(WallType::WallLava);

	for (int i = 0; i < 3; i++)
	{
		lava_wall.setPosition(sf::Vector2f(liquid_pos.x, liquid_pos.y - 3));
		liquid_pos.x += 16 * 2;
		this->front_walls.push_back(lava_wall);
	}
}

void RoomDemon::initEnemies()
{
	sf::Vector2f pos = this->getPosition();

	this->enemies.push_back(new Demon());
	this->enemies.at(this->enemies.size() - 1)->setPosition(sf::Vector2f(pos.x + 16 * 5, pos.y + 16 * 3));

	this->enemies.push_back(new Demon());
	this->enemies.at(this->enemies.size() - 1)->setPosition(sf::Vector2f(pos.x + 16 * 14, pos.y + 16 * 10));
}
