#pragma once
#include"GameScene.h"

/*-------------------------------------------------------------------------------------------
	MenueScene class:
	- entry scene of the game
	- loading resources are realised in the main thread
-------------------------------------------------------------------------------------------*/

class MenueScene : public GameScene
{
private:

	//------PRIVATE METHODS------
	
	// 'MainMenue' scene logic
	virtual void logic();

	// load graphical/audio resources
	virtual void loadResources();

	// delete all resources, free memory
	virtual void dispose();

public:

	//------CONSTRUCTOR/DESTRUCTOR------	

	// default constructor
	MenueScene();

	// destuctor => delete all menue objects
	~MenueScene();

	//------METHODS------

	// start 'MainMenue' scene thread
	virtual void start();

	// wait 'MainMenue' scene thread
	virtual void stop();

	// draw whole 'MainMenue' scene
	virtual void draw(sf::RenderTarget& target);
};