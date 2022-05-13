#pragma once
#include"../../headers/tools/GameLog.h"
#include"../../headers/GameCycle.h"
#include"SFML/Graphics.hpp"

/*-------------------------------------------------------------------------------------------
	GameScene class:
	- represents some one part of the game
	- abstract class
	- has draw method
	- loading resources can be realised in the main or logic_thread thread 
-------------------------------------------------------------------------------------------*/

class GameScene
{
protected:

	bool isLoaded;				// if resources are loaded

	bool isEventSent;			// if event was sent to the game cycle

	sf::Thread logic_thread;	// thread that handles game scene logic

	//------PRIVATE METHODS------
	
	// game scene logic
	virtual void logic() = 0;

	// load graphical/audio resources
	virtual void loadResources() = 0;

	// delete all resources, free memory
	virtual void dispose() = 0;

public:

	//------CONSTRUCTOR------	

	// default constructor with thread initializing
	GameScene() :logic_thread(&GameScene::logic, this)
	{
		this->isLoaded = false;
		this->isEventSent = false;
	}

	// destructor => delete game scene objects
	virtual ~GameScene()
	{

	}

	//------METHODS------

	// start game scene thread
	virtual void start() = 0;

	// wait gamescene thread
	virtual void stop() = 0;

	// draw whole game scene
	virtual void draw(sf::RenderTarget& target) = 0;

	// reset event sent process state
	virtual void resetEventSent() = 0;

	bool getIsLoaded()
	{
		return this->isLoaded;
	}
};