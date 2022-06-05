#include"../../src/headers/render/GameRender.h"

sf::View GameRender::rview;

//------Constructor/Destructor definition------

GameRender::GameRender()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;

	this->resetView();
	this->rwindow = new sf::RenderWindow(Settings::video_mode,Settings::getWindowTitle(),sf::Style::Fullscreen,settings);
	this->rwindow->setView(this->rview);

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

		gs.draw(*this->rwindow);

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

void GameRender::resetView()
{
	this->rview.reset(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(Settings::video_mode.width, Settings::video_mode.height)));
}

void GameRender::updateView()
{
	this->rwindow->setView(this->rview);
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
	if (Settings::vertical_sync == false) this->rwindow->setFramerateLimit(Settings::frame_limit);
	else
	{
		this->rwindow->setVerticalSyncEnabled(Settings::vertical_sync);
		this->rwindow->setFramerateLimit(0);
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