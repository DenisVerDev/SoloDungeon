#pragma once
#include"Scene.h"
#include"SFML/Graphics.hpp"

/*-------------------------------------------------------------------------------------------
	GameScene class:
	- represents some one part of the game
	- abstract class
	- loading resources can be realised in the main or logic_thread thread 
-------------------------------------------------------------------------------------------*/

class GameScene : public Scene
{
protected:

	bool isLoaded;				// if resources are loaded

	sf::Thread logic_thread;	// thread that handles game scene logic

	//------PRIVATE METHODS------

	// game scene logic
	virtual void logic() = 0;

	// load graphical/audio resources
	virtual void loadResources() = 0;

public:

	//------CONSTRUCTOR------	

	// default constructor with thread initializing
	GameScene() : Scene(),logic_thread(&GameScene::logic, this)
	{
		this->isLoaded = false;
	}

	//------METHODS------

	// start game scene thread
	virtual void start() = 0;

	bool getIsLoaded()
	{
		return this->isLoaded;
	}
};