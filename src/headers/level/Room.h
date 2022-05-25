#pragma once
#include"Floor.h"
#include"Wall.h"
#include"Door.h"
#include"../../headers/entities/Player.h"

/*-------------------------------------------------------------------------------------------
	Room class:
	- room where player and enemies are playing together
-------------------------------------------------------------------------------------------*/

class Player;

enum class RoomType
{
	UndeadRoom,
	OrcRoom,
	SlimeRoom,
	DemonRoom,
	BossRoom
};

class Room
{

private:

	//------ROOM COMPONENTS------

	Floor floor;

	std::vector<Wall> front_walls;
	std::vector<Wall> leftright_walls;
	std::vector<Wall> back_walls;
	
	std::vector<Door> doors;

	//------PRIVATE VARS------

	RoomType type;

	sf::Vector2i floor_size;

	//------PRIVATE METHODS------

	// init room objects
	void initObjects();

public:

	// constructor with position and type
	Room(sf::Vector2f pos, RoomType type);

	//------METHODS------

	// draw room's floor
	void drawFloor(sf::RenderTarget& target);

	// draw room's front and leftright walls
	void drawFrontWalls(sf::RenderTarget& target);

	// draw room's back walls
	void drawBackWalls(sf::RenderTarget& target);

	// draw room's front door
	void drawFrontDoor(sf::RenderTarget& target);

	// draw room's back door
	void drawBackDoor(sf::RenderTarget& target);

	// anim front walls[MUST BE PRIVATE]
	void animWalls();

	// set texture for all room's objects
	void setTexture(sf::Texture& texture);

	// set entry point for the player
	void setEntryPoint(Player& player);

	//------GETTERS------

	sf::Vector2f getPosition();

	sf::Vector2i getSize();

};