#include"../../src/headers/render/GameRender.h"

//------Constructor/Destructor definition------

GameRender::GameRender()
{
	this->rwindow = new sf::RenderWindow(Settings::video_mode,Settings::getWindowTitle(),sf::Style::Fullscreen);
	
	this->setRefreshRate();
	this->setIcon();
}

GameRender::~GameRender()
{
	delete this->rwindow;
	this->rwindow = nullptr;

	GameLog::log("Main window was destroyed!");
}

//------Methods definition------

void GameRender::render(GameScene& gs)
{
	try
	{
		this->rwindow->clear();

		// draw stuff

		this->rwindow->display();
	}
	catch (std::exception& e)
	{
		GameException ge(e, __FILE__, __LINE__);
		GameLog::log(ge);
	}
}

void GameRender::stopRender()
{
	this->rwindow->close();
	
	GameLog::log("Render process was stopped!");
}

void GameRender::updateSettings()
{
	this->setRefreshRate();
}

bool GameRender::listenEvent(sf::Event& system_event)
{
	return this->rwindow->pollEvent(system_event);
}

const bool GameRender::running() const
{
	return this->rwindow->isOpen();
}

//------Private methods definition------

void GameRender::setRefreshRate()
{
	this->rwindow->setVerticalSyncEnabled(Settings::vertical_sync);

	if (Settings::dependency_mode == FrameDependency::Free) this->rwindow->setFramerateLimit(0);
	else
	{
		if(Settings::vertical_sync == false) this->rwindow->setFramerateLimit(Settings::getFrameLimit());
		else this->rwindow->setFramerateLimit(0);
	}
}

void GameRender::setIcon()
{
	std::string icon_file_name = Settings::getIconFileName();
	if (icon_file_name != "NONE")
	{
		sf::Image icon;
		if (icon.loadFromFile(GameResources::icons_path + icon_file_name))
		{
			sf::Vector2u icon_size = icon.getSize();
			this->rwindow->setIcon(icon_size.x, icon_size.y, icon.getPixelsPtr());
		}
	}
}