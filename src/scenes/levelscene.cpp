#include"../../src/headers/scenes/LevelScene.h"

//------Constructor/Destructor definition------

LevelScene::LevelScene() : GameScene()
{
	example_text.setFont(GameResources::text_font);
	example_text.setCharacterSize(64);
	example_text.setFillColor(sf::Color::Red);
	example_text.setString("GAMEPLAY IS IN PROGRESS");

	this->player = new Player();
	this->player->setPosition(sf::Vector2f(300, 300));

	GameLog::log("Level scene was initialized!");
}

LevelScene::~LevelScene()
{
	// deleting player
	delete this->player;
	this->player = nullptr;

	this->logic_thread.wait();	 // wait thread to stop

	GameLog::log("Level scene was destroyed!");
}

//------Methods definition------

void LevelScene::start()
{
	this->logic_thread.launch();

	GameLog::log("Level scene thread has started!");
}

void LevelScene::stop()
{
	this->logic_thread.wait();
	GameLog::log("Level scene thread has stopped!");
}


void LevelScene::logic()
{
	if (this->isLoaded == false) this->loadResources();	// loading resources in different thread

	// logic here
	while (GameCycle::getCurrentState() == GameState::Gameplay)
	{
		this->player->behave();
	}
}

void LevelScene::draw(sf::RenderTarget& target)
{
	try
	{
		if (this->isLoaded == true)
		{
			target.draw(this->example_text);
			this->player->draw(target);
		}
	}
	catch (std::exception& e)
	{
		GameException ge("Levele scene drawing exception", e, GeType::Rendering, __FILE__, __LINE__);
		GameLog::log(ge);
	}
}

void LevelScene::loadResources()
{
	// load resources
	this->player->loadTexture();

	//end
	this->isLoaded = true;
	GameLog::log("Level scene resources are loaded!");
}


void LevelScene::resetEventSent()
{
	this->isEventSent = false;
}