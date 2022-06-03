#include"../../src/headers/level/RoomSlime.h"

RoomSlime::RoomSlime(sf::Vector2f pos) : Room(pos)
{
	this->room_name = "THE SLIME ROOM";

	// init all room objects and enemies
	this->initObjects();
	this->initEnemies();
}

void RoomSlime::initObjects()
{
	this->buildDefRoom();

	// flag initialization
	sf::Vector2f flag_pos = this->front_walls[3].getPosition();

	Wall flag(WallType::WallFlagBlue);
	flag.setPosition(sf::Vector2f(flag_pos.x, flag_pos.y + 4));	// 4 is wall top height

	this->front_walls.push_back(flag);

	// water walls initialization
	sf::Vector2f liquid_pos = this->front_walls[6].getPosition(); // water walls position

	Wall water_wall(WallType::WallWater);

	for (int i = 0; i < 3; i++)
	{
		water_wall.setPosition(sf::Vector2f(liquid_pos.x, liquid_pos.y + 4));
		liquid_pos.x += 16 * 2;
		this->front_walls.push_back(water_wall);
	}
}

void RoomSlime::initEnemies()
{
	sf::Vector2f pos = this->getPosition();

	this->enemies.push_back(new Slime());
	this->enemies.at(this->enemies.size() - 1)->setPosition(sf::Vector2f(pos.x + 16 * 2, pos.y + 16 * 2));

	this->enemies.push_back(new Slime());
	this->enemies.at(this->enemies.size() - 1)->setPosition(sf::Vector2f(pos.x + 16 * 2, pos.y + 16 * 14));

	this->enemies.push_back(new Slime());
	this->enemies.at(this->enemies.size() - 1)->setPosition(sf::Vector2f(pos.x + 16 * 5, pos.y + 16 * 3));

	this->enemies.push_back(new Slime());
	this->enemies.at(this->enemies.size() - 1)->setPosition(sf::Vector2f(pos.x + 16 * 14, pos.y + 16 * 6));
}
