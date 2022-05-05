#include"headers/Settings.h"

//------Initializing constants------
const unsigned int Settings::max_frame_limit = 144;
const unsigned int Settings::min_frame_limit = 30;
const std::string Settings::icons_path = "res/icons/";
const sf::VideoMode Settings::video_mode = sf::VideoMode::getFullscreenModes()[0]; //gets the highest resolution possible

//------Initializing variables------
unsigned int Settings::frame_limit = 60;

float Settings::music_volume = 100.f;
float Settings::sound_volume = 100.f;

bool Settings::vertical_sync = false;

std::string Settings::window_title = "Standart game window";
std::string Settings::iconfile_name = "NONE";

FrameDependency Settings::dependency_mode = FrameDependency::Dependent;

//------Methods definition------
void Settings::applySettings() //[TODO]:1
{

}

void Settings::saveSettings() //save settings to file
{
	std::string path = "configs/settings.conf";
	std::ofstream ostream;

	try
	{
		ostream.open(path);

		if (ostream.good())
		{
			ostream << "frame_limit=" << Settings::frame_limit << "\n";
			ostream << "vertical_sync=" << Settings::vertical_sync << "\n";
			ostream << "music_volume=" << Settings::music_volume << "\n";
			ostream << "sound_volume=" << Settings::sound_volume << "\n";
			ostream << "iconfile_name=" << Settings::iconfile_name << "\n";
			ostream << "window_title=" << Settings::window_title << "\n";
			ostream << "dependency_mode=" << (int)Settings::dependency_mode << "\n";
		}

		ostream.close();
	}
	catch (std::exception& e)
	{
		ostream.close();

		GameException ge("Failed to save settings to file!", e, GeType::Settings, __FILE__, __LINE__);
	}
}

void Settings::loadSettings() //load settings from file
{
	std::string path = "configs/settings.conf";
	std::ifstream istream;

	try
	{
		istream.open(path);

		if (istream.good())
		{
			std::string buff;

			std::getline(istream, buff, '=');
			unsigned int fl;
			istream >> fl;
			Settings::setFrameLimit(fl);
			rEnd(istream, buff)

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
			//- dont require rEnd there because [>>] stops at first space

			std::getline(istream, buff, '=');
			istream >> Settings::dependency_mode;
			rEnd(istream, buff)

		}

		istream.close();
	}
	catch (std::exception& e)
	{
		istream.close();
		Settings::setStandartSettings();

		GameException ge("Failed to load settings to file!", e, GeType::Settings, __FILE__, __LINE__);
	}
}

//------Setters definition------
void Settings::setStandartSettings()
{
	Settings::setFrameLimit(60);
	Settings::vertical_sync = false;
	Settings::dependency_mode = FrameDependency::Dependent;
	Settings::setMusicVolume(100.f);
	Settings::setSoundVolume(100.f);
	Settings::setWindowTitle("Standart game window");
	Settings::setIconFileName("NONE");
}

void Settings::setFrameLimit(unsigned int frame_limit)
{
	if (frame_limit >= Settings::min_frame_limit && frame_limit <= Settings::max_frame_limit) Settings::frame_limit = frame_limit;
	else Settings::frame_limit = 60;
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
	std::string fullpath = Settings::icons_path + filename;
	try
	{
		struct stat buffer;
		if (stat(fullpath.c_str(), &buffer) == 0) Settings::iconfile_name = filename;
		else Settings::iconfile_name = "NONE";
	}
	catch (std::exception& e)
	{
		Settings::iconfile_name = "NONE";

		GameException ge(e, __FILE__, __LINE__); //standart exception
	}
}

void Settings::setWindowTitle(std::string title)
{
	if (!title.empty()) Settings::window_title = title;
	else Settings::window_title = "Standart game window";
}

void Settings::setDependencyMode(unsigned int dependecy_mode)
{
	if (dependecy_mode == 0 || dependecy_mode == 1) Settings::dependency_mode = (FrameDependency)dependecy_mode;
	else Settings::dependency_mode = FrameDependency::Dependent;
}

//------Getters definition------
int Settings::getFrameLimit()
{
	return Settings::frame_limit;
}

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

//------Overload operators definition------
std::ifstream& operator>>(std::ifstream& stream, FrameDependency& fd)
{
	int idm; //int dependecy_mode
	stream >> idm;
	Settings::setDependencyMode(idm);
	return stream;
}
