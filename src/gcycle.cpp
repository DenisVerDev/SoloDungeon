#include"../src/headers/GameCycle.h"

//------Constructor/Destructor definition------

GameCycle::GameCycle()
{
	Settings::loadSettings();

	this->gscene = new GameScene();
	this->grender = new GameRender();
}

GameCycle::~GameCycle()
{
	delete this->gscene;
	this->gscene = nullptr;

	delete this->grender;
	this->grender = nullptr;

	GameLog::log("Destroyed game scene and render object!");
}

//------Methods definition------

void GameCycle::start()
{
	try
	{
		GameLog::log("Game cycle started!");
		while (this->grender->running()) // main thread, only render and handling events
		{
			// event handler
			this->handleEvents();

			// render game scene
			this->grender->render(*this->gscene);
		}
	}
	catch (std::exception& e)
	{
		GameException ge(e, __FILE__, __LINE__);
		GameLog::log(ge);

		this->kill();
	}
}

void GameCycle::handleEvents()
{
	while (this->grender->listenEvent(this->system_event))
	{
		switch (this->system_event.type)
		{

			case sf::Event::Closed:
				this->kill();
				break;
		}
	}
}

void GameCycle::kill() // this method may be useless!!! need to check it on later versions of the game
{
	this->grender->stopRender(); // everything relies on render -> without image on screen, there is no point in game
}
