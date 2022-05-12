#include"../../src/headers/tools/GameResources.h"

//------Initializing constants------

const std::string GameResources::icons_path = "res/icons/";
const std::string GameResources::gui_path = "res/gui/";

const std::string GameResources::log_path = "logs/logs.log";
const std::string GameResources::exc_log_path = "logs/exceptions.log";

const std::string GameResources::settings_path = "configs/settings.conf";

const std::string GameResources::fonts_path = "res/fonts/";

//------Initializing fonts------

sf::Font GameResources::head_font;

sf::Font GameResources::text_font;

//------Initializing colors------

sf::Color GameResources::text_color = sf::Color::White;
sf::Color GameResources::hover_text_color = sf::Color::Yellow;

sf::Color GameResources::additional_color = sf::Color(105, 105, 105);

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

void GameResources::changeColors()
{
	switch (GameCycle::getCurrentState())
	{
		case GameState::MainMenue:
			GameResources::text_color = sf::Color::White;
			GameResources::hover_text_color = sf::Color::Yellow;
			GameResources::additional_color = sf::Color(105, 105, 105);
			break;
	}
}
