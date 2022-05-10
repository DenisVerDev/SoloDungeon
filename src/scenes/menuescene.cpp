#include"../../src/headers/scenes/MenueScene.h"

//------Constructor/Destructor definition------

MenueScene::MenueScene() : GameScene()
{
	// initializing objects


	GameLog::log("Menue scene was initialized!");
}

MenueScene::~MenueScene()
{
	// delete objects

	this->dispose();

	GameLog::log("Menue scene was destroyed!");
}

//------Methods definition------

void MenueScene::start()
{
	if(this->isLoaded == false) this->loadResources();
	this->logic_thread.launch();

	GameLog::log("Menue scene thread has started!");
}

void MenueScene::stop()
{
	this->logic_thread.wait();
	GameLog::log("Menue scene thread has stopped!");
}

void MenueScene::loadResources()
{
	// load resources

	//end
	this->isLoaded = true;
	GameLog::log("Menue scene resources are loaded!");
}

void MenueScene::logic()
{
	// logic here
	while (GameCycle::getCurrentState() == GameState::MainMenue)
	{

	}
}

void MenueScene::draw(sf::RenderTarget& target)
{
	// drawing here
}

void MenueScene::dispose()
{
	// dispose resources

	this->logic_thread.wait(); // wait thread to stop
	GameLog::log("Menue scene resources were disposed!");
}
