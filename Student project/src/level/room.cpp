#include"../../src/headers/level/Room.h"

//------Constructor/Destructor definition------

Room::Room(sf::Vector2f pos)
{
	this->isTracked = false;
	this->isCleared = false;
	this->isFinished = false;

	// init floor
	this->floor_size.y = 256;
	this->floor_size.x = 256;

	this->floor.setSize(this->floor_size);
	this->floor.setPosition(pos);
}

Room::~Room()
{
	// deleting enemies
	for (auto e : this->enemies)
	{
		delete e;
		e = nullptr;
	}
}

//------Methods definition------

void Room::buildDefRoom()
{
	Wall w_front(WallType::WallFront);
	Wall w_back(WallType::WallBottom);
	Wall w_left(WallType::WallLeft);
	Wall w_right(WallType::WallRight);
	Wall w_leftb(WallType::WallLeft_b);
	Wall w_rightb(WallType::WallRight_b);

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

	// wall bottom borders
	w_leftb.setPosition(sf::Vector2f(pos.x - w_left.getSize().x, pos.y + this->floor_size.y - w_front.getSize().y));
	w_rightb.setPosition(sf::Vector2f(pos.x + this->floor_size.x, pos.y - w_front.getSize().y + this->floor_size.y));

	this->back_walls.push_back(w_leftb);
	this->back_walls.push_back(w_rightb);
}

void Room::update(Entity& player)
{
	// collision between room area and player,enemies
	sf::IntRect room_collision = this->getCollision();
	ICollision::collision(player, room_collision);
	for (auto e : this->enemies)
	{
		ICollision::collision(*e, room_collision);
	}

	// checking collision between player, entities and columns
	for (Wall& wall : this->front_walls)
	{
		if (wall.getWallType() == WallType::Column)
		{
			ICollision::collision(player, wall);
			for (auto e : this->enemies)
			{
				ICollision::collision(*e, wall);
			}
		}
	}

	// player and enemies behaviours
	if (this->isCleared == false)
	{

		// collision between enemies only
		int vec_size = this->enemies.size();
		for (int i = 0; i < vec_size; i++)
		{
			for (int j = 0; j < vec_size; j++)
			{
				if (i != j && this->enemies[i]->getIsAlive() == true && this->enemies[j]->getIsAlive() == true)
				{
					ICollision::collision(*this->enemies[i], *this->enemies[j]);
				}
			}
		}

		// track the player
		if (this->isTracked == false) this->trackPlayer(player);

		// player attack check
		if (player.getAttack() == true)
		{
			for (auto e : this->enemies)
			{
				player.attack(*e);
			}
		}

		// enemies behaviour
		for (auto e : this->enemies)
		{
			e->update();
		}

		// check if room is cleared or not
		this->clearCheck();
	}
	else if(this->doors[0].getState() == DoorState::Closed)
	{
		this->doors[0].setState(DoorState::Opened); // open the door to the next room
	}
	else if (this->isFinished == false) // check if player is near exit
	{
		this->finishCheck(player);
	}

	// animation update - walls
	this->animWalls();
}

void Room::drawFloor(sf::RenderTarget& target)
{
	this->floor.draw(target);
}

void Room::drawFrontWalls(sf::RenderTarget& target)
{
	for (Wall& w : this->front_walls)
	{
		w.draw(target);
	}

	for (Wall& w : this->leftright_walls)
	{
		w.draw(target);
	}
}

void Room::drawBackWalls(sf::RenderTarget& target)
{
	for (Wall& w : this->back_walls)
	{
		w.draw(target);
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

void Room::drawEnemies(sf::RenderTarget& target)
{
	// draw dead bodies
	for (auto e : this->enemies)
	{
		if(e->getIsAlive() == false) e->draw(target);
	}

	// draw alive enemies
	for (auto e : this->enemies)
	{
		if(e->getIsAlive() == true) e->draw(target);
	}
}

void Room::trackPlayer(Entity& player)
{
	for (auto e : this->enemies)
	{
		e->track(player);
	}

	this->isTracked = true;
}

void Room::animWalls()
{
	for (Wall& w : this->front_walls)
	{
		WallType type = w.getWallType();
		if (type == WallType::WallLava || type == WallType::WallWater) w.updateAnim();
	}
}

void Room::clearCheck()
{
	int dead_count = std::count_if(this->enemies.begin(), this->enemies.end(), [](Enemy* e) {return e->getIsAlive() == false; });
	int enemy_count = this->enemies.size();

	if (dead_count == enemy_count) this->isCleared = true;
}

void Room::finishCheck(Entity& player)
{
	sf::Vector2f player_pos = player.getPosition();
	sf::Vector2f door_pos = this->doors[0].getPosition();
	sf::Vector2f door_size = this->doors[0].getSize();

	// X axis check
	if (player_pos.x >= door_pos.x && player_pos.x <= door_pos.x + door_size.x)
	{
		// Y axis check
		if (player_pos.y <= door_pos.y + door_size.y) this->isFinished = true;
	}
}

//------Setters definition------

void Room::setTexture(sf::Texture& texture)
{
	// floor
	this->floor.setTexture(texture);

	// front walls
	for (Wall& w : this->front_walls)
	{
		w.setTexture(texture);
	}

	// left-right walls
	for (Wall& w : this->leftright_walls)
	{
		w.setTexture(texture);
	}

	// back walls
	for (Wall& w : this->back_walls)
	{
		w.setTexture(texture);
	}

	// doors
	for (Door& d : this->doors)
	{
		d.setTexture(texture);
	}

	// enemies
	for (auto e : this->enemies)
	{
		e->setTexture(texture);
	}
}

void Room::setEntryPoint(Entity& player)
{
	float x = this->getPosition().x + this->getSize().x / 2.f;
	float y = this->getPosition().y + this->getSize().y /1.5f;
	player.setPosition(sf::Vector2f(x,y));
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

sf::IntRect Room::getCollision()
{
	sf::Vector2i pos(this->getPosition());
	pos.y += 8;

	sf::Vector2i size(this->getSize());
	size.y -= 30;

	return sf::IntRect(pos, size);;
}

bool Room::getIsFinished()
{
	return this->isFinished;
}

std::string Room::getRoomName()
{
	return this->room_name;
}
