#include"../../src/headers/render/GameRender.h"

//------Constructor/Destructor definition------

GameRender::GameRender(sf::Event& system_event)
{
	this->rwindow = new sf::RenderWindow(Settings::video_mode,Settings::getWindowTitle(),sf::Style::Fullscreen);
	
	this->setRefreshRate();
	this->setIcon();

	this->rwindow->pollEvent(system_event);
}

GameRender::~GameRender()
{
	delete this->rwindow;
	this->rwindow = nullptr;
}

//------Methods definition------

void GameRender::render(GameScene& gs)
{
	this->rwindow->clear();

	// render stuff

	this->rwindow->display();
}

const bool GameRender::isRunning() const
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
		icon.loadFromFile(GameResources::icons_path + icon_file_name);

		sf::Vector2u icon_size = icon.getSize();
		this->rwindow->setIcon(icon_size.x, icon_size.y, icon.getPixelsPtr());
	}
}