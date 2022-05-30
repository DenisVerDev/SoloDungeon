#include"../../src/headers/level/RoomBoss.h"

RoomBoss::RoomBoss(sf::Vector2f pos) : Room(pos)
{
	this->floor_size.x = 512;
	this->floor.setSize(this->floor_size);

	// init all room objects and enemies
	this->initObjects();
	this->initEnemies();
}

void RoomBoss::initObjects()
{
	this->buildDefRoom();

	// water and lava walls initialization
	Wall water_wall(WallType::WallWater);
	Wall lava_wall(WallType::WallLava);

	sf::Vector2f liquid_lava = this->front_walls[1].getPosition();
	sf::Vector2f liquid_water = this->front_walls[16].getPosition();

	for (int i = 0; i < 6; i++)
	{
		lava_wall.setPosition(sf::Vector2f(liquid_lava.x, liquid_lava.y - 3));
		liquid_lava.x += 16 * 2;
		this->front_walls.push_back(lava_wall);

		water_wall.setPosition(sf::Vector2f(liquid_water.x, liquid_water.y + 4));
		liquid_water.x += 16 * 2;
		this->front_walls.push_back(water_wall);
	}

	// columns initialization
	sf::Vector2f pos = this->getPosition();

	Wall column(WallType::Column);

	column.setPosition(sf::Vector2f(pos.x + 16 * 5, pos.y + 16 * 2));
	this->front_walls.push_back(column);
	column.setPosition(sf::Vector2f(pos.x + 16 * 5, pos.y + 16 * 8));
	this->front_walls.push_back(column);

	column.setPosition(sf::Vector2f(pos.x + 16 * 26, pos.y + 16 * 2));
	this->front_walls.push_back(column);
	column.setPosition(sf::Vector2f(pos.x + 16 * 26, pos.y + 16 * 8));
	this->front_walls.push_back(column);
}

void RoomBoss::initEnemies()
{

}
