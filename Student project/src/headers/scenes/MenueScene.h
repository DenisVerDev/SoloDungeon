#pragma once
#include"GameScene.h"
#include"../../headers/gui/GameButton.h"
#include"../../headers/gui/SettingsMenue.h"

/*-------------------------------------------------------------------------------------------
	MenueScene class:
	- entry scene of the game
	- loading resources are realised in the main thread
-------------------------------------------------------------------------------------------*/

class GameButton;
class SettingsMenue;

class MenueScene : public GameScene
{
private:

	//------SCENE COMPONENTS------

	sf::Text game_title;		// big game title

	sf::Text author_credit;		// author info

	GameButton* btn_new_game;	// new game button

	GameButton* btn_settings;	// settings button

	GameButton* btn_quit;		// quit from the game

	SettingsMenue* smenue;		// settings menue

	//------PRIVATE METHODS------
	
	// 'MainMenue' scene logic
	virtual void logic();

	// handle buttons click event
	void buttonsClickHandle();

	// load graphical/audio resources
	virtual void loadResources();

public:

	//------CONSTRUCTOR/DESTRUCTOR------	

	// default constructor
	MenueScene();

	// destuctor => delete all menue objects
	~MenueScene();

	//------METHODS------

	// start 'MainMenue' scene thread
	virtual void start();

	// draw whole 'MainMenue' scene
	virtual void draw(sf::RenderTarget& target);

	// reset event sent process state
	virtual void resetEventSent();
};