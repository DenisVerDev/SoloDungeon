#pragma once
#include"GameScene.h"
#include"../../headers/level/Floor.h"
#include"../../headers/level/Wall.h"
#include"../../headers/entities/Player.h"
#include"../../headers/tools/GameLog.h"

/*-------------------------------------------------------------------------------------------
	LevelScene class:
-------------------------------------------------------------------------------------------*/

class Player;

class LevelScene : public GameScene
{
private:

	sf::Text example_text;

	Player* player;

	Floor* floor;

	std::vector<Wall> walls;

	//------RESOURCES------

	sf::Texture levelmain_texture;	// all main static level objects

	//------PRIVATE METHODS------

	// Level scene logic
	virtual void logic();

	// load graphical/audio resources
	virtual void loadResources();

public:

	//------CONSTRUCTOR/DESTRUCTOR------	

	// default constructor
	LevelScene();

	// destuctor => delete all Level objects
	~LevelScene();

	//------METHODS------

	// start Level scene thread
	virtual void start();

	// wait Level scene thread
	virtual void stop();

	// draw whole Level scene
	virtual void draw(sf::RenderTarget& target);

	// reset event sent process state
	virtual void resetEventSent();
};