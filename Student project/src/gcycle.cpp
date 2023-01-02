#include"../src/headers/GameCycle.h"

//------Initializing static variables------

GameState GameCycle::gstate = GameState::MainMenue;

std::vector<GameEvent> GameCycle::game_events;

MouseData GameCycle::mouse_data;

bool GameCycle::running = false;

bool GameCycle::isSM = false;

//------Constructor/Destructor definition------

GameCycle::GameCycle() : gamelog_thread(&GameLog::handleLogs)
{
	srand(time(NULL));
	Settings::loadSettings();
	GameInput::loadInput();

	GameResources::initColors();
	GameResources::loadFonts();
	GameResources::loadAudio();

	this->mscene = new MenueScene();

	this->grender = new GameRender();

	AudioManager::playMusic(); // start playing background music
}

GameCycle::~GameCycle()
{
	// stop background music
	AudioManager::stopMusic();

	// free music and sounds
	AudioManager::free();

	// free memory
	this->destroyGameScene((GameScene*&)this->mscene);
	this->destroyGameScene((GameScene*&)this->lscene);

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

		// main menue thread -- entry scene

		this->mscene->start();
		
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
				case GameState::MainMenue:
					this->grender->render(*this->mscene);
					break;

				case GameState::Gameplay:
					this->grender->render(*this->lscene);
					break;
			}

			this->grender->updateView();

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
				GameLog::log("Game event: settings update!");
				this->grender->updateSettings(); // update render settings
				AudioManager::updateSettings(Settings::getMusicVolume(),Settings::getSoundVolume()); // update audio settings
				Settings::saveSettings(); // save settings to file
				this->resetEventSent();
				break;

			case GameEvent::StartSM:
				GameLog::log("Game event: settings menue opened!");
				this->isSM = true;
				this->resetEventSent();
				break;

			case GameEvent::EndSM:
				GameLog::log("Game event: settings menue closed!");
				this->isSM = false;
				this->resetEventSent();
				break;

			case GameEvent::Quit:
				GameLog::log("Game event: quit from the game!");
				this->kill();
				this->resetEventSent();
				break;

			case GameEvent::SetMainMenue:
				GameLog::log("Game event: start main menue!");
				this->mscene = new MenueScene();
				this->gstate = GameState::MainMenue;
				this->destroyGameScene((GameScene*&)this->lscene);
				this->grender->resetView();
				this->mscene->start();
				break;

			case GameEvent::SetGameplay:
				GameLog::log("Game event: start gameplay!");
				this->lscene = new LevelScene();
				this->gstate = GameState::Gameplay;
				this->destroyGameScene((GameScene*&)this->mscene);
				GameRender::rview.zoom(0.5f);
				this->lscene->start();
				break;

		}
	}
}

void GameCycle::addGameEvent(GameEvent game_event)
{
	GameCycle::game_events.push_back(game_event);
}

void GameCycle::resetEventSent() // only if we don't change scenes
{
	if (this->gstate == GameState::MainMenue) this->mscene->resetEventSent();
}

void GameCycle::destroyGameScene(GameScene*& scene)
{
	delete scene;
	scene = nullptr;
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