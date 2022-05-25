#include"../../src/headers/level/Room.h"

Room::Room(sf::Vector2f pos, RoomType type)
{
	this->type = type;

	this->floor.setPosition(pos);

	// init all room objects
	this->initObjects();
}

//------Methods definition------

void Room::initObjects()
{
	// init floor
	this->floor_size.y = 256;
	if (this->type != RoomType::BossRoom) this->floor_size.x = 256;
	else this->floor_size.x = 512;
	this->floor.setSize(this->floor_size);


	Wall w_front(WallType::WallFront);
	Wall w_back(WallType::WallBottom);
	Wall w_left(WallType::WallLeft);
	Wall w_right(WallType::WallRight);
	Wall w_leftb(WallType::WallLeft_b);
	Wall w_rightb(WallType::WallRight_b);
	Wall flag(WallType::WallFlagYell);
	Wall column(WallType::Column);
	Wall water_wall(WallType::WallWater);
	Wall lava_wall(WallType::WallLava);

	sf::Vector2f pos = this->getPosition();

	int count_x = this->floor_size.x / 16;
	int count_y = this->floor_size.y / 16;

	// top and bottom walls
	for (int i = 0; i < count_x; i++)
	{
		w_front.setPosition(sf::Vector2f(pos.x + i * 16, pos.y - w_front.getSize().y));
		w_back.setPosition(sf::Vector2f(pos.x + i * 16, pos.y + this->floor_size.y - w_back.getSize().y));

		this->front_walls.push_back(w_front);
		this->back_walls.push_back(w_back);
	}

	//  left and right walls
	for (int i = 0; i < count_y; i++)
	{
		w_left.setPosition(sf::Vector2f(pos.x - w_left.getSize().x, pos.y - w_front.getSize().y + i * 16));
		w_right.setPosition(sf::Vector2f(pos.x + this->floor_size.x, pos.y - w_front.getSize().y + i * 16));

		this->leftright_walls.push_back(w_left);
		this->leftright_walls.push_back(w_right);
	}

	// doors
	int door_index = (count_x / 2) - 2;

	Door door;
	door.setState(DoorState::Closed);

	sf::Vector2f door_pos = this->front_walls.at(door_index).getPosition();
	door.setPosition(sf::Vector2f(door_pos.x, pos.y - door.getSize().y));
	this->doors.push_back(door);

	std::vector<Wall>::iterator begin = this->front_walls.begin() + door_index;
	std::vector<Wall>::iterator end = begin + 4;
	this->front_walls.erase(begin, end);

	door_pos = this->back_walls.at(door_index).getPosition();
	door.setPosition(sf::Vector2f(door_pos.x, pos.y + this->floor_size.y - door.getSize().y));
	this->doors.push_back(door);

	//begin = this->back_walls.begin() + door_index;
	//end = begin + 4;
	//this->back_walls.erase(begin, end);

	// wall bottom borders
	w_leftb.setPosition(sf::Vector2f(pos.x - w_left.getSize().x, pos.y + this->floor_size.y - w_front.getSize().y));
	w_rightb.setPosition(sf::Vector2f(pos.x + this->floor_size.x, pos.y - w_front.getSize().y + this->floor_size.y));

	this->back_walls.push_back(w_leftb);
	this->back_walls.push_back(w_rightb);

	// flag initialization
	sf::Vector2f flag_pos = this->front_walls[3].getPosition();
	flag.setPosition(sf::Vector2f(flag_pos.x, flag_pos.y + 4));	// 4 is wall top height

	// water and lava walls position
	sf::Vector2f liquid_pos = this->front_walls[6].getPosition();

	switch (this->type)
	{
		case RoomType::UndeadRoom:
			this->front_walls.push_back(flag);
			break;

		case RoomType::OrcRoom:
			flag.setType(WallType::WallFlagGreen);
			this->front_walls.push_back(flag);
			
			for (int i = 1; i < 5; i++)
			{
				column.setPosition(sf::Vector2f(pos.x + 16 * i*3, pos.y + 16 * 3));
				this->front_walls.push_back(column);

				column.setPosition(sf::Vector2f(pos.x + 16 * i * 3, pos.y + 16 * 8));
				this->front_walls.push_back(column);
			}
			break;

		case RoomType::SlimeRoom:
			flag.setType(WallType::WallFlagBlue);
			this->front_walls.push_back(flag);

			for (int i = 0; i < 3; i++)
			{
				water_wall.setPosition(sf::Vector2f(liquid_pos.x, liquid_pos.y + 4));
				liquid_pos.x += 16*2;
				this->front_walls.push_back(water_wall);
			}
			break;

		case RoomType::DemonRoom:
			flag.setType(WallType::WallFlagRed);
			this->front_walls.push_back(flag);

			for (int i = 0; i < 3; i++)
			{
				lava_wall.setPosition(sf::Vector2f(liquid_pos.x, liquid_pos.y - 3));
				liquid_pos.x += 16 * 2;
				this->front_walls.push_back(lava_wall);
			}
			break;

		case RoomType::BossRoom:
			sf::Vector2f liquid_lava = this->front_walls[1].getPosition();
			sf::Vector2f liquid_water = this->front_walls[16].getPosition();

			// water and lava walls
			for (int i = 0; i < 6; i++)
			{
				lava_wall.setPosition(sf::Vector2f(liquid_lava.x, liquid_lava.y - 3));
				liquid_lava.x += 16 * 2;
				this->front_walls.push_back(lava_wall);

				water_wall.setPosition(sf::Vector2f(liquid_water.x, liquid_water.y + 4));
				liquid_water.x += 16 * 2;
				this->front_walls.push_back(water_wall);
			}

			// columns
			column.setPosition(sf::Vector2f(pos.x + 16 * 5, pos.y + 16 * 2));
			this->front_walls.push_back(column);
			column.setPosition(sf::Vector2f(pos.x + 16 * 5, pos.y + 16 * 8));
			this->front_walls.push_back(column);

			column.setPosition(sf::Vector2f(pos.x + 16 * (count_x-6), pos.y + 16 * 2));
			this->front_walls.push_back(column);
			column.setPosition(sf::Vector2f(pos.x + 16 * (count_x - 6), pos.y + 16 * 8));
			this->front_walls.push_back(column);
			break;
	}
}

void Room::drawFloor(sf::RenderTarget& target)
{
	this->floor.draw(target);
}

void Room::drawFrontWalls(sf::RenderTarget& target)
{
	int vec_size = this->front_walls.size();
	for (int i = 0; i < vec_size; i++)
	{
		this->front_walls[i].draw(target);
	}

	vec_size = this->leftright_walls.size();
	for (int i = 0; i < vec_size; i++)
	{
		this->leftright_walls[i].draw(target);
	}
}

void Room::drawBackWalls(sf::RenderTarget& target)
{
	int vec_size = this->back_walls.size();
	for (int i = 0; i < vec_size; i++)
	{
		this->back_walls[i].draw(target);
	}
}

void Room::drawFrontDoor(sf::RenderTarget& target)
{
	this->doors[0].draw(target);
}

void Room::drawBackDoor(sf::RenderTarget& target)
{
	this->doors[1].draw(target);
}

void Room::animWalls()
{
	int vec_size = this->front_walls.size();
	for (int i = 0; i < vec_size; i++)
	{
		WallType type = this->front_walls[i].getWallType();
		if (type == WallType::WallLava || type == WallType::WallWater) this->front_walls[i].updateAnim();
	}
}

void Room::setTexture(sf::Texture& texture)
{
	// floor
	this->floor.setTexture(texture);

	// front walls
	int vec_size = this->front_walls.size();
	for (int i = 0; i < vec_size; i++)
		this->front_walls[i].setTexture(texture);

	// left-right walls
	vec_size = this->leftright_walls.size();
	for (int i = 0; i < vec_size; i++)
		this->leftright_walls[i].setTexture(texture);

	// back walls
	vec_size = this->back_walls.size();
	for (int i = 0; i < vec_size; i++)
		this->back_walls[i].setTexture(texture);

	// doors
	vec_size = this->doors.size();
	for (int i = 0; i < vec_size; i++)
		this->doors[i].setTexture(texture);
}

void Room::setEntryPoint(Player& player)
{
	float x = this->getPosition().x + this->getSize().x / 2.f;
	float y = this->getPosition().y + this->getSize().y /1.5f;
	player.setPosition(sf::Vector2f(x,y), true);
}

//------Getters definition------

sf::Vector2f Room::getPosition()
{
	return this->floor.getPosition();
}

sf::Vector2i Room::getSize()
{
	return this->floor_size;
}