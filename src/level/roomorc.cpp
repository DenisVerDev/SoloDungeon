#include"../../src/headers/level/RoomOrc.h"


RoomOrc::RoomOrc(sf::Vector2f pos) : Room(pos)
{
	this->room_name = "THE ORC ROOM";

	// init all room objects and enemies
	this->initObjects();
	this->initEnemies();
}


void RoomOrc::initObjects()
{
	this->buildDefRoom();

	// flag initialization
	sf::Vector2f flag_pos = this->front_walls[3].getPosition();

	Wall flag(WallType::WallFlagGreen);
	flag.setPosition(sf::Vector2f(flag_pos.x, flag_pos.y + 4));	// 4 is wall top height

	this->front_walls.push_back(flag);

	// columns initialization
	sf::Vector2f pos = this->getPosition();

	Wall column(WallType::Column);

	for (int i = 1; i < 5; i++)
	{
		column.setPosition(sf::Vector2f(pos.x + 16 * i * 3, pos.y + 16 * 3));
		this->front_walls.push_back(column);

		column.setPosition(sf::Vector2f(pos.x + 16 * i * 3, pos.y + 16 * 8));
		this->front_walls.push_back(column);
	}
}

void RoomOrc::initEnemies()
{
	sf::Vector2f pos = this->getPosition();

	this->enemies.push_back(new Orc());
	this->enemies.at(this->enemies.size() - 1)->setPosition(sf::Vector2f(pos.x + 16 * 2, pos.y + 16 * 2));

	this->enemies.push_back(new Orc());
	this->enemies.at(this->enemies.size() - 1)->setPosition(sf::Vector2f(pos.x + 16 * 14, pos.y + 16 * 2));

	this->enemies.push_back(new Orc());
	this->enemies.at(this->enemies.size() - 1)->setPosition(sf::Vector2f(pos.x + 16 * 15, pos.y + 16 * 7));
}
