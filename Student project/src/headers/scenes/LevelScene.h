#pragma once
#include"GameScene.h"
#include"../../headers/level/RoomUndead.h"
#include"../../headers/level/RoomOrc.h"
#include"../../headers/level/RoomSlime.h"
#include"../../headers/level/RoomDemon.h"
#include"../../headers/level/RoomBoss.h"
#include"../../headers/entities/Player.h"
#include"../../headers/gui/Hud.h"
#include"../../headers/tools/GameLog.h"
#include"SFML/Audio.hpp"

/*-------------------------------------------------------------------------------------------
	LevelScene class:
-------------------------------------------------------------------------------------------*/

class Room;
class Player;
class Hud;

class LevelScene : public GameScene
{
private:

	Player* player;
	
	std::vector<Room*> rooms;		// level rooms with enemies

	int current_room;				// in which room is player at the moment

	Hud* hud;						// player's HUD

	sf::Text result_text;			// game result text(win or lose)
	sf::Text tip_text;				// tip text(press esc to leave)

	bool result;					// if game has a result
	bool show_result;				// if game can show player's result

	//------RESOURCES------

	sf::Texture levelmain_texture;	// all main static level objects

	sf::Sound lose_sound;			// sound when player is dead
	sf::Sound win_sound;			// sound when player has won

	//------PRIVATE METHODS------

	// Level scene logic
	virtual void logic();

	// load graphical/audio resources
	virtual void loadResources();

	// init all level rooms and bridges
	void initLevelObjects();

	// check for the result and show it
	void checkResult();

public:

	//------CONSTRUCTOR/DESTRUCTOR------	

	// default constructor
	LevelScene();

	// destuctor => delete all Level objects
	~LevelScene();

	//------METHODS------

	// start Level scene thread
	virtual void start();

	// draw whole Level scene
	virtual void draw(sf::RenderTarget& target);

	// reset event sent process state
	virtual void resetEventSent();
};