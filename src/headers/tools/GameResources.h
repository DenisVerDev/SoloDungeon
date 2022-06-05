#pragma once
#include<string>
#include"GameLog.h"
#include"GameException.h"
#include"SFML/Graphics.hpp"

/*-------------------------------------------------------------------------------------------
	GameResources class:
	- stores all constant paths
	- stores all game related resources
	- private constructor => only static functions and variables
	- loads resources
-------------------------------------------------------------------------------------------*/

class GameResources
{

private:

	GameResources();						// private constructor

public:

	//------CONSTANT PATHS------

	static const std::string icons_path;	  // path where all icons are
	static const std::string gui_path;		  // path to all gui files
	static const std::string level_path;	  // path to all level objects textures

	static const std::string log_path;		// path to file with standart logs
	static const std::string exc_log_path;	// path to log file with exceptions

	static const std::string settings_path;		// path to settings config file
	static const std::string gameinput_path;	// path to game input config file

	static const std::string fonts_path;	// path to all game fonts

	static const std::string audio_path;	// path to all game fonts

	//------FONTS------

	static sf::Font head_font;				// font for headers

	static sf::Font text_font;				// font for simple texts

	//------COLORS------

	static sf::Color text_color;			// MenueScene text color
	static sf::Color hover_text_color;	// MenueScene text hover color

	static sf::Color additional_color;		// additional information text color

	//------METHODS------

	// load all game fonts
	static void loadFonts();

	// load all game audio
	static void loadAudio();

	// init all text colors
	static void initColors();
};