#include"../../src/headers/scenes/MenueScene.h"

//------Constructor/Destructor definition------

MenueScene::MenueScene() : GameScene()
{
	// game title initialization
	this->game_title.setFont(GameResources::head_font);
	this->game_title.setCharacterSize(100);
	this->game_title.setFillColor(sf::Color::Yellow);
	this->game_title.setString(Settings::getWindowTitle());
	this->game_title.setStyle(sf::Text::Bold);
	
	float width = this->game_title.getLocalBounds().width;
	float height = this->game_title.getLocalBounds().height;
	sf::Vector2f game_title_pos((Settings::video_mode.width / 2.f) - (width/1.8f), (Settings::video_mode.height / 2.f) - height*3);

	this->game_title.setPosition(game_title_pos);
	
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
	try
	{
		// drawing game logo
		target.draw(this->game_title);
	}
	catch (std::exception& e)
	{
		GameException ge("Menue scene drawing exception", e, GeType::Rendering, __FILE__, __LINE__);
		GameLog::log(ge);
	}
}

void MenueScene::dispose()
{
	// dispose resources

	this->logic_thread.wait(); // wait thread to stop
	GameLog::log("Menue scene resources were disposed!");
}
