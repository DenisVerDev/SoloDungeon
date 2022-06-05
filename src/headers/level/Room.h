#pragma once
#include"Floor.h"
#include"Wall.h"
#include"Door.h"
#include"../../headers/entities/Enemy.h"

/*-------------------------------------------------------------------------------------------
	Room class:
	- room where player and enemies are playing together
	- abstract class
-------------------------------------------------------------------------------------------*/

class Room : public ICollision
{

protected:

	//------ROOM COMPONENTS------

	Floor floor;

	std::vector<Wall> front_walls;
	std::vector<Wall> leftright_walls;
	std::vector<Wall> back_walls;
	
	std::vector<Door> doors;

	std::vector<Enemy*> enemies;

	std::string room_name;

	//------PRIVATE VARS------

	sf::Vector2i floor_size;

	bool isTracked;					// if player is tracked by enemies

	bool isCleared;					// if player killed everyone in the room

	bool isFinished;				// if player is going out of the room through the front door

	//------PRIVATE METHODS------

	// build default room with walls, doors and floor
	void buildDefRoom();

	// init room objects
	virtual void initObjects() = 0;

	// init room enemies
	virtual void initEnemies() = 0;

	// anim front walls
	void animWalls();

	// check if room is cleared
	void clearCheck();

	// check if player leaves the room
	void finishCheck(Entity& player);

public:

	// constructor with position
	Room(sf::Vector2f pos);

	// destructor
	~Room();

	//------METHODS------

	// update room's logic based on player's actions
	virtual void update(Entity& player);

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

	// draw room's enemies
	void drawEnemies(sf::RenderTarget& target);

	// all room's enemies will track player's actions
	void trackPlayer(Entity& player);

	//------SETTERS------

	// set texture for all room's objects
	void setTexture(sf::Texture& texture);

	// set entry point for the player
	void setEntryPoint(Entity& player);

	//------GETTERS------

	sf::Vector2f getPosition();

	sf::Vector2i getSize();

	// get room's collision
	virtual sf::IntRect getCollision();

	// get if player complete and exit the room
	bool getIsFinished();

	// get room's name
	std::string getRoomName();
};