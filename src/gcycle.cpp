#include"../src/headers/GameCycle.h"

//------Initializing static variables------

GameState GameCycle::gstate = GameState::Gameplay;

std::vector<GameEvent> GameCycle::game_events;

MouseData GameCycle::mouse_data;

bool GameCycle::running = false;

//------Constructor/Destructor definition------

GameCycle::GameCycle() : gamelog_thread(&GameLog::handleLogs)
{
	Settings::loadSettings();

	this->gscene = new GameScene();
	this->grender = new GameRender();
}

GameCycle::~GameCycle()
{
	// free memory
	delete this->gscene;
	this->gscene = nullptr;

	delete this->grender;
	this->grender = nullptr;

	// stop game log thread
	this->running = false;
	gamelog_thread.wait();
}

//------Methods definition------

void GameCycle::start()
{
	try
	{
		this->running = true;

		GameLog::log("Game cycle started!");

		// game log thread

		gamelog_thread.launch();
		
		// main thread

		while (this->grender->running()) // main thread, only render and handling events
		{
			// system event handler
			this->handleSystemEvents();

			// game event handler
			this->handleGameEvents();

			// render game scenes depending on current game state
			switch (this->gstate)
			{
				case GameState::Gameplay:
					this->grender->render(*this->gscene);
					break;
			}

		}
	}
	catch (std::exception& e)
	{
		GameException ge(e, __FILE__, __LINE__);
		GameLog::log(ge);
	}

}

void GameCycle::handleSystemEvents()
{
	while (this->grender->listenEvent(this->system_event))
	{
		switch (this->system_event.type)  // handling system events for main window behaviour
		{

			case sf::Event::Closed:
				this->kill();
				break;
		}

		// handling system events for different needs
		mouse_data.updateData(this->system_event);
	}
}

void GameCycle::handleGameEvents()
{
	int size = GameCycle::game_events.size();
	if (size > 0)
	{
		GameLog::log("Game events count: "+std::to_string(size));

		GameEvent ev = GameCycle::game_events.at(0);
		GameCycle::game_events.erase(GameCycle::game_events.begin());

		switch (ev)
		{
			case GameEvent::SettingsUpdate:
				this->grender->updateSettings();
				GameLog::log("Game event: settings update!");
				break;
		}
	}
}

void GameCycle::addGameEvent(GameEvent game_event)
{
	GameCycle::game_events.push_back(game_event);
}

void GameCycle::kill()
{
	this->gstate = GameState::Kill;
	this->grender->stopRender(); // everything relies on render -> without image on screen, there is no point in game
}

//------Getters definition------

GameState GameCycle::getCurrentState()
{
	return GameCycle::gstate;
}