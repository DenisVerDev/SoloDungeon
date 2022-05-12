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
	
	float video_width = Settings::video_mode.width;
	float video_height = Settings::video_mode.height;

	float text_width = this->game_title.getLocalBounds().width;
	float text_height = this->game_title.getLocalBounds().height;
	
	float game_title_x = dt::getCenteredPostion(sf::Vector2f(video_width,video_height), sf::Vector2f(text_width, text_height), sf::Vector2f(0,0)).x;
	sf::Vector2f game_title_pos(game_title_x, (video_height / 2.f) - text_height * 3);

	this->game_title.setPosition(game_title_pos);

	// new game button
	this->btn_new_game = new GameButton("Start new game");
	
	float btn_x = game_title_pos.x + this->btn_new_game->getWidth() / 1.5f;
	float btn_y = game_title_pos.y + 300;
	this->btn_new_game->setPosition(sf::Vector2f(btn_x, btn_y));

	// settings button

	this->btn_settings = new GameButton("Settings");
	this->btn_settings->setPosition(sf::Vector2f(btn_x, btn_y += 100));

	// quit button
	sf::Vector2f btn_set_pos = this->btn_settings->getPosition();
	
	this->btn_quit = new GameButton("Quit");
	this->btn_quit->setPosition(sf::Vector2f(btn_x, btn_y += 100));

	// author credit

	this->author_credit.setPosition(10, Settings::video_mode.height - 60);
	this->author_credit.setFont(GameResources::text_font);
	this->author_credit.setCharacterSize(20);
	this->author_credit.setFillColor(GameResources::additional_color);
	this->author_credit.setStyle(sf::Text::Style::Bold);
	this->author_credit.setString("author of this demo: Denis V\nemail: denisverepadev@gmail.com");

	GameLog::log("Menue scene was initialized!");
}

MenueScene::~MenueScene()
{
	// delete objects
	delete this->btn_new_game;
	this->btn_new_game = nullptr;

	delete this->btn_settings;
	this->btn_settings = nullptr;

	delete this->btn_quit;
	this->btn_quit = nullptr;

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
		if (GameCycle::isPaused == false)
		{
			try
			{
				sf::Vector2f mouse_pos(GameCycle::mouse_data.getPosition());	// get cursor position

				// update button states
				this->btn_new_game->update(mouse_pos);
				this->btn_settings->update(mouse_pos);
				this->btn_quit->update(mouse_pos);

				// handle buttons click event
				this->buttonsClickHandle();
			}
			catch (std::exception& e)
			{
				GameException ge("Menue scene logic exception!", e, GeType::Logic, __FILE__, __LINE__);
				GameLog::log(ge);
			}
		}
		else
		{
			// settings menue logic here
		}
	}
}

void MenueScene::buttonsClickHandle()
{
	if (this->btn_new_game->getIsClicked() && this->isEventSent == false)	// start new game
	{

	}

	if (this->btn_settings->getIsClicked() && this->isEventSent == false)	// open settings menue
	{
		this->isEventSent = true;
		GameCycle::addGameEvent(GameEvent::StartPause);
	}

	if (this->btn_quit->getIsClicked() && this->isEventSent == false)	// quit from game
	{
		this->isEventSent = true;
		GameCycle::addGameEvent(GameEvent::Quit); 
	}

}

void MenueScene::draw(sf::RenderTarget& target)
{
	try
	{
		if (GameCycle::isPaused == false)
		{
			// drawing game logo
			target.draw(this->game_title);
			// drawing buttons
			this->btn_new_game->draw(target);
			this->btn_settings->draw(target);
			this->btn_quit->draw(target);
		}
		else
		{
			// draw settings menue here
		}

		// drawing author credit
		target.draw(this->author_credit);
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
