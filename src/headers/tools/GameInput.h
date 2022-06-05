#pragma once
#include<vector>
#include<fstream>
#include"GameResources.h"
#include"SFML/Window.hpp"

/*-------------------------------------------------------------------------------------------
	GameInput class:
	- stores corresponding list of player actions and trigger buttons
	- to change game control settings, you have to make changes in config file
	- private constructor
-------------------------------------------------------------------------------------------*/

// player actions in the game

enum class PlayerAction
{
	Default,
	MoveUp,
	MoveDown,
	MoveRight,
	MoveLeft,
	Back,
	Attack
};

class GameInput
{
private:

	// private constructor
	GameInput();

	//------PRIVATE VARS------	

	static std::vector<std::pair<PlayerAction,sf::Keyboard::Key>> key_actions;			// actions that activate by key pressing
	static std::vector<std::pair<PlayerAction, sf::Mouse::Button>> mouse_actions;		// actions that activate by mouse button pressing

	//------PRIVATE METHODS------	
	
	// save game input to config
	static void saveInput();

public:

	//------CONSTANTS------	

	static const int key_actions_count;			// count of player key actions
	static const int mouse_actions_count;		// count of player mouse actions

	//------METHODS------	

	// set standart game input
	static void setStandartInput();

	// load game input from config
	static void loadInput();

	//------GETTERS------	

	// get key from action
	static sf::Keyboard::Key getKeyByAction(PlayerAction action);

	// get mouse button from action
	static sf::Mouse::Button getButtonByAction(PlayerAction action);

	// get player's action from key_actions
	static PlayerAction getActionByKey(sf::Keyboard::Key key);

	// get player's action from mouse_actions
	static PlayerAction getActionByMouse(sf::Mouse::Button button);

	// get player's action by string
	static PlayerAction getActionByName(std::string action);

	// get name of the player's action
	static std::string getActionString(PlayerAction action);
};