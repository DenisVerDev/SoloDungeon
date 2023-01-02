#pragma once
#include<string>
#include<fstream>
#include"../../headers/tools/DifferentTools.h"
#include"../../headers/tools/GameException.h"
#include"../../headers/tools/GameLog.h"
#include"../../headers/tools/GameResources.h"
#include"../../headers/GameCycle.h"
#include<SFML/Window.hpp>

/*-------------------------------------------------------------------------------------------
	All settings can be divided in two categories:
	1) settings that can be changed during the gameplay					->	changeable
	2) settings that are initialized from the start and not changeable	->	non changeable

	Settings class:
	- stores all necessary infornation about rendering process and audio settings
	- private constructor => only static functions and variables
	- setter for 'iconfile_name' checks if such file exist, if negative => NONE
	- saves settings in file
	- loads settings from file
-------------------------------------------------------------------------------------------*/

class Settings
{
private:

	Settings();		//private constructor in order to avoid making an object of this class

	//------PRIVATE VARS------

	static float music_volume;	
	static float sound_volume;	

	static std::string iconfile_name;			// non changeable
	static std::string window_title;			// non changeable

public:

	//------CONSTANTS------

	static const unsigned int frame_limit;

	static const sf::VideoMode video_mode;		// non changeable | only one video mode
	
	//------PUBLIC VARS------

	static bool vertical_sync;

	//------METHODS------

	// save settings to file
	static void saveSettings(); 

	// load settings from file
	static void loadSettings(); 

	// reset settings to standart
	static void setStandartSettings();

	//------SETTERS------

	static void setVerticalSync(bool vertical_sync);
	static void setMusicVolume(float volume);
	static void setSoundVolume(float volume);
	static void setIconFileName(std::string filename);
	static void setWindowTitle(std::string title);

	//------GETTERS------

	static float getMusicVolume();
	static float getSoundVolume();
	static std::string getIconFileName();
	static std::string getWindowTitle();

};