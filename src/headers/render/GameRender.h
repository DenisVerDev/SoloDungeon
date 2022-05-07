#pragma once
#include"SFML/Graphics.hpp"
#include"Settings.h"
#include"../../headers/GameScene.h"

/*-------------------------------------------------------------------------------------------
	GameRender class:
	- renders all game objects
	- frame dependency mode work is realised in GameScene class
	- render process works in the main thread
	- core of the game's visual
-------------------------------------------------------------------------------------------*/

class GameRender
{
private:

	sf::RenderWindow* rwindow;			    // main window pointer

	//------PRIVATE METHODS------			

	// set render behaviour based on settings
	void setRefreshRate();

	// set window's icon
	void setIcon();

public:

	// public constructor
	GameRender();

	// destructor => frees memory from the main window
	~GameRender();

	//------METHODS------

	// renders everything(game scene, menues, etc.)
	void render(GameScene& gs);

	// stop render process by closing the main window
	void stopRender();

	/*
		Main window listens for an event:
		true => new event has come,
		false => nothing new
	*/
	bool listenEvent(sf::Event& system_event);

	// if main window is open
	const bool running() const;
};