#include"../../src/headers/scenes/MenueScene.h"

//------Constructor/Destructor definition------

MenueScene::MenueScene() : GameScene()
{
	// game title initialization
	this->game_title.setFont(GameResources::head_font);
	this->game_title.setCharacterSize(100);
	this->game_title.setFillColor(GameResources::hover_text_color);
	this->game_title.setString(Settings::getWindowTitle());
	this->game_title.setStyle(sf::Text::Bold);
	
	float video_width = Settings::video_mode.width;
	float video_height = Settings::video_mode.height;

	float title_width = this->game_title.getLocalBounds().width;
	float title_height = this->game_title.getLocalBounds().height;
	
	float game_title_x = dt::getCenteredPostion(sf::Vector2f(video_width,video_height), sf::Vector2f(title_width, title_height), sf::Vector2f(0.f,0.f)).x;
	sf::Vector2f game_title_pos(game_title_x, (video_height / 2.f) - title_height * 3);

	this->game_title.setPosition(game_title_pos);

	// new game button
	this->btn_new_game = new GameButton("Start new game");
	this->btn_new_game->setSize(sf::Vector2f(208.f, 40.f));
	
	float btn_x = dt::getCenteredPostion(sf::Vector2f(video_width, video_height), this->btn_new_game->getSize(), sf::Vector2f(0.f, 0.f)).x;
	float btn_y = game_title_pos.y + 300;
	this->btn_new_game->setPosition(sf::Vector2f(btn_x, btn_y));

	// settings button
	this->btn_settings = new GameButton("Settings");
	this->btn_settings->setSize(sf::Vector2f(116.f, 46.f));

	btn_x = dt::getCenteredPostion(sf::Vector2f(video_width, video_height), this->btn_settings->getSize(), sf::Vector2f(0.f, 0.f)).x;
	this->btn_settings->setPosition(sf::Vector2f(btn_x, btn_y += 100));

	// quit button
	this->btn_quit = new GameButton("Quit");
	this->btn_quit->setSize(sf::Vector2f(75.f, 40.f));

	btn_x = dt::getCenteredPostion(sf::Vector2f(video_width, video_height), this->btn_quit->getSize(), sf::Vector2f(0.f, 0.f)).x;
	this->btn_quit->setPosition(sf::Vector2f(btn_x, btn_y += 100));

	// author credit
	this->author_credit.setPosition(10, Settings::video_mode.height - 60);
	this->author_credit.setFont(GameResources::text_font);
	this->author_credit.setCharacterSize(20);
	this->author_credit.setFillColor(GameResources::additional_color);
	this->author_credit.setStyle(sf::Text::Style::Bold);
	this->author_credit.setString("author of this demo: Denis V\nemail: denisverepadev@gmail.com");

	// settings menue
	this->smenue = new SettingsMenue();
	sf::Vector2f smenue_pos = dt::getCenteredPostion(sf::Vector2f(video_width, video_height), this->smenue->getSize(), sf::Vector2f(0, 0));
	this->smenue->setPosition(smenue_pos);

	GameLog::log("Menue scene was initialized!");
}

MenueScene::~MenueScene()
{
	this->logic_thread.wait(); // wait thread to stop

	// delete objects
	delete this->btn_new_game;
	this->btn_new_game = nullptr;

	delete this->btn_settings;
	this->btn_settings = nullptr;

	delete this->btn_quit;
	this->btn_quit = nullptr;

	delete this->smenue;
	this->smenue = nullptr;

	GameLog::log("Menue scene was destroyed!");
}

//------Methods definition------

void MenueScene::start()
{
	this->logic_thread.launch();

	GameLog::log("Menue scene thread has started!");
}

void MenueScene::logic()
{
	// logic here
	while (GameCycle::getCurrentState() == GameState::MainMenue)
	{
		if (GameCycle::isSM == false)
		{
			try
			{
				// update button states
				this->btn_new_game->update(GameCycle::mouse_data);
				this->btn_settings->update(GameCycle::mouse_data);
				this->btn_quit->update(GameCycle::mouse_data);

				// handle buttons click event
				this->buttonsClickHandle();
			}
			catch (std::exception& e)
			{
				GameException ge("Main menue scene logic exception!", e, GeType::Logic, __FILE__, __LINE__);
				GameLog::log(ge);
			}
		}
		else
		{
			try
			{
				// settings menue logic here
				this->smenue->logic();
			}
			catch (std::exception& e)
			{
				GameException ge("Settings menue logic exception!", e, GeType::Logic, __FILE__, __LINE__);
				GameLog::log(ge);
			}
		}
	}
}

void MenueScene::buttonsClickHandle()
{
	if (this->btn_new_game->getIsClicked() && this->isEventSent == false)	// start new game
	{
		this->isEventSent = true;
		GameCycle::addGameEvent(GameEvent::SetGameplay);
	}

	if (this->btn_settings->getIsClicked() && this->isEventSent == false)	// open settings menue
	{
		this->smenue->setSettings();

		this->isEventSent = true;
		GameCycle::addGameEvent(GameEvent::StartSM);
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
		if (GameCycle::isSM == false)
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
			this->smenue->draw(target);
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

void MenueScene::loadResources()
{
	// load resources

	//end
	this->isLoaded = true;
	GameLog::log("Menue scene resources are loaded!");
}

void MenueScene::resetEventSent()
{
	this->isEventSent = false;
	this->smenue->resetEventSent();
}
