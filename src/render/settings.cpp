#include"../../src/headers/render/Settings.h"

//------Initializing constants------

const unsigned int Settings::frame_limit = 144; // comfort frame limit

const sf::VideoMode Settings::video_mode = sf::VideoMode::getFullscreenModes()[0]; //gets the highest resolution possible

//------Initializing variables------

float Settings::music_volume = 100.f;
float Settings::sound_volume = 100.f;

bool Settings::vertical_sync = false;

std::string Settings::window_title = "Standart game window";
std::string Settings::iconfile_name = "NONE";

//------Methods definition------

void Settings::saveSettings() //save settings to file
{
	std::ofstream ostream;

	try
	{
		ostream.open(GameResources::settings_path);

		if (ostream.good())
		{
			ostream << "vertical_sync=" << Settings::vertical_sync << "\n";
			ostream << "music_volume=" << Settings::music_volume << "\n";
			ostream << "sound_volume=" << Settings::sound_volume << "\n";
			ostream << "iconfile_name=" << Settings::iconfile_name << "\n";
			ostream << "window_title=" << Settings::window_title << "\n";

			GameLog::log("Settings were successfully saved!");
		}
	}
	catch (std::exception& e)
	{
		GameException ge("Failed to save settings to file!", e, GeType::Settings, __FILE__, __LINE__);
		GameLog::log(ge);
	}

	ostream.close();
}

void Settings::loadSettings() //load settings from file
{
	std::ifstream istream;

	try
	{
		istream.open(GameResources::settings_path);

		if (istream.good())
		{
			std::string buff;

			std::getline(istream, buff, '=');
			istream >> Settings::vertical_sync;
			rEnd(istream, buff)

			std::getline(istream, buff, '=');
			float mv;
			istream >> mv;
			Settings::setMusicVolume(mv);
			rEnd(istream, buff)

			std::getline(istream, buff, '=');
			float sv;
			istream >> sv;
			Settings::setSoundVolume(sv);
			rEnd(istream, buff)

			std::getline(istream, buff, '=');
			std::string iconfn;
			istream >> iconfn;
			Settings::setIconFileName(iconfn);
			rEnd(istream, buff)

			std::getline(istream, buff, '=');
			std::string wt;
			std::getline(istream, wt);
			Settings::setWindowTitle(wt);

			GameLog::log("Settings were successfully loaded!");
		}
	}
	catch (std::exception& e)
	{
		Settings::setStandartSettings();

		GameException ge("Failed to load settings to file!", e, GeType::Settings, __FILE__, __LINE__);
		GameLog::log(ge);
	}

	istream.close();
}

//------Setters definition------

void Settings::setStandartSettings()
{
	Settings::setVerticalSync(false);
	Settings::setMusicVolume(100.f);
	Settings::setSoundVolume(100.f);

	GameLog::log("Settings have been reset!");
}

void Settings::setVerticalSync(bool vertical_sync)
{
	Settings::vertical_sync = vertical_sync;
}

void Settings::setMusicVolume(float volume)
{
	if (volume >= 0.f && volume <= 100.f) Settings::music_volume = volume;
	else Settings::music_volume = 100.f;
}

void Settings::setSoundVolume(float volume)
{
	if (volume >= 0.f && volume <= 100.f) Settings::sound_volume = volume;
	else Settings::sound_volume = 100.f;
}

void Settings::setIconFileName(std::string filename)
{
	std::string fullpath = GameResources::icons_path + filename;
	try
	{
		struct stat buffer;
		if (stat(fullpath.c_str(), &buffer) == 0) Settings::iconfile_name = filename;
		else
		{
			Settings::iconfile_name = "NONE";
			GameLog::log("Such icon does not exist or file is corrupted!");
		}
	}
	catch (std::exception& e)
	{
		Settings::iconfile_name = "NONE";

		GameException ge(e, __FILE__, __LINE__); //standart exception
		GameLog::log(ge);
	}
}

void Settings::setWindowTitle(std::string title)
{
	if (!title.empty()) Settings::window_title = title;
	else Settings::window_title = "Standart game window";
}

//------Getters definition------

float Settings::getMusicVolume()
{
	return Settings::music_volume;
}

float Settings::getSoundVolume()
{
	return Settings::sound_volume;
}

std::string Settings::getIconFileName()
{
	return Settings::iconfile_name;
}

std::string Settings::getWindowTitle()
{
	return Settings::window_title;
}
