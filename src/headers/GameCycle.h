#pragma once
#include"../headers/render/GameRender.h"
#include"../headers/tools/MouseData.h"

/*-------------------------------------------------------------------------------------------
	GameCycle class:
	- main core of the game
	- render, update and work with files are separated in different threads
	[TODO]:1
	- every thread's lifespan should be based on the main window state(grender state)
-------------------------------------------------------------------------------------------*/

class GameCycle
{

private:

	//------PRIVATE VARS------	

	sf::Event system_event;			// system window event

	GameRender* grender;			// renders everything on screen

	GameScene* gscene;				// contains game objects and realise game logic

public:

	//------STATIC VARS------	

	static MouseData mouse_data;

	//------CONSTRUCTOR/DESTRUCTOR------	

	// public constructor
	GameCycle();

	// destructor => frees all memory
	~GameCycle();

	//------METHODS------	

	// start game cycle
	void start();

	// handle window's system events
	void handleSystemEvents();		

	// end game process
	void kill();				// this method may be useless!!! need to check it on later versions of the game
};