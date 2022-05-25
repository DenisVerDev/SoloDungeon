#pragma once
#include"GameScene.h"
#include"../../headers/level/Room.h"
#include"../../headers/entities/Player.h"
#include"../../headers/tools/GameLog.h"

/*-------------------------------------------------------------------------------------------
	LevelScene class:
-------------------------------------------------------------------------------------------*/

class Room;
class Player;

class LevelScene : public GameScene
{
private:

	Player* player;

	std::vector<Room*> rooms;		// level rooms with enemies

	int current_room;				// in which room is player at the moment

	//------RESOURCES------

	sf::Texture levelmain_texture;	// all main static level objects

	//------PRIVATE METHODS------

	// Level scene logic
	virtual void logic();

	// load graphical/audio resources
	virtual void loadResources();

	// init all level rooms and bridges
	void initLevelObjects();

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