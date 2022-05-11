#pragma once
#include"../../headers/gui/GameButton.h"
#include"GameScene.h"

/*-------------------------------------------------------------------------------------------
	MenueScene class:
	- entry scene of the game
	- loading resources are realised in the main thread
-------------------------------------------------------------------------------------------*/

class MenueScene : public GameScene
{
private:

	//------MENUE COMPONENTS------

	sf::Text game_title;		// big game title

	sf::Text author_credit;		// author info

	GameButton btn_new_game;	// new game button

	GameButton btn_settings;	// settings button

	GameButton btn_quit;		// quit from the game

	//------PRIVATE METHODS------
	
	// 'MainMenue' scene logic
	virtual void logic();

	// handle buttons click event
	void buttonsClickHandle();

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