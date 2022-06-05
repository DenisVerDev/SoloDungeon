#include"../../src/headers/tools/GameResources.h"

//------Initializing constants------

const std::string GameResources::icons_path = "res/icons/";
const std::string GameResources::gui_path = "res/gui/";
const std::string GameResources::level_path = "res/level/";

const std::string GameResources::log_path = "logs/logs.log";
const std::string GameResources::exc_log_path = "logs/exceptions.log";

const std::string GameResources::settings_path = "configs/settings.conf";
const std::string GameResources::gameinput_path = "configs/input.conf";

const std::string GameResources::fonts_path = "res/fonts/";

const std::string GameResources::audio_path = "res/audio/";

//------Initializing fonts------

sf::Font GameResources::head_font;

sf::Font GameResources::text_font;

//------Initializing colors------

sf::Color GameResources::text_color;
sf::Color GameResources::hover_text_color;

sf::Color GameResources::additional_color;

//------Methods definition------

void GameResources::loadFonts()
{
	try
	{
		if (!GameResources::head_font.loadFromFile(GameResources::fonts_path + "Bitmgothic.ttf"))
		{
			throw GameException("Failed to load head font!", GeType::Resources, __FILE__, __LINE__);
		}

		if (!GameResources::text_font.loadFromFile(GameResources::fonts_path + "dpcomic.ttf"))
		{
			throw GameException("Failed to load text font!", GeType::Resources, __FILE__, __LINE__);
		}
		
		GameLog::log("All fonts were loaded!");
	}
	catch (std::exception& e)
	{
		GameLog::log(e);
	}
}

void GameResources::loadAudio()
{
	try
	{
		if (AudioManager::loadAudio(GameResources::audio_path))
		{
			GameLog::log("Audio was loaded!");
		}
		else throw GameException("Audio was not loaded!", GeType::Logic, __FILE__, __LINE__);
	}
	catch (std::exception& e)
	{
		GameLog::log(e);
	}

	AudioManager::updateSettings(Settings::getMusicVolume(), Settings::getSoundVolume());
}

void GameResources::initColors()
{
	GameResources::text_color = sf::Color::White;
	GameResources::hover_text_color = sf::Color::Yellow;
	GameResources::additional_color = sf::Color(105, 105, 105);
}
