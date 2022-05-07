#pragma once
#include"SFML/Window.hpp"
#include"SFML/Graphics.hpp"
#include"Settings.h"
#include"../../headers/GameScene.h"

/*-------------------------------------------------------------------------------------------
	GameRender class:
	- renders all game objects
	- frame dependency mode is realised in GameScene class
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

	// public constructor with Event parameter
	GameRender(sf::Event& system_event);

	// destructor => frees memory when game process is killed
	~GameRender();

	//------METHODS------

	// renders whole game scene
	void render(GameScene& gs);

	// if main window is open
	const bool isRunning() const;
};