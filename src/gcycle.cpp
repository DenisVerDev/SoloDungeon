#include"../src/headers/GameCycle.h"

//------Initializing static variables------

GameState GameCycle::gstate = GameState::Gameplay;

std::vector<GameEvent> GameCycle::game_events;

MouseData GameCycle::mouse_data;

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

		this->kill();
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

void GameCycle::kill() // this method may be useless!!! need to check it on later versions of the game
{
	this->grender->stopRender(); // everything relies on render -> without image on screen, there is no point in game
}

//------Getters definition------

GameState GameCycle::getCurrentState()
{
	return GameCycle::gstate;
}
