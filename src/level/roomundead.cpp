#include"../../src/headers/level/RoomUndead.h"

RoomUndead::RoomUndead(sf::Vector2f pos) : Room(pos)
{
	this->room_name = "THE UNDEAD ROOM";

	// init all room objects and enemies
	this->initObjects();
	this->initEnemies();
}

void RoomUndead::initObjects()
{
	this->buildDefRoom();

	// flag initialization
	sf::Vector2f flag_pos = this->front_walls[3].getPosition();

	Wall flag(WallType::WallFlagYell);
	flag.setPosition(sf::Vector2f(flag_pos.x, flag_pos.y + 4));	// 4 is wall top height

	this->front_walls.push_back(flag);
}

void RoomUndead::initEnemies()
{
	sf::Vector2f pos = this->getPosition();

	this->enemies.push_back(new Undead());
	this->enemies.at(this->enemies.size() - 1)->setPosition(sf::Vector2f(pos.x + 16 * 4, pos.y + 16 * 2));

	this->enemies.push_back(new Undead());
	this->enemies.at(this->enemies.size() - 1)->setPosition(sf::Vector2f(pos.x + 16 * 4, pos.y + 16 * 6));

	this->enemies.push_back(new Undead());
	this->enemies.at(this->enemies.size() - 1)->setPosition(sf::Vector2f(pos.x + 16 * 8, pos.y + 16 * 3));

	this->enemies.push_back(new Undead());
	this->enemies.at(this->enemies.size() - 1)->setPosition(sf::Vector2f(pos.x + 16 * 14, pos.y + 16 * 4));
}
