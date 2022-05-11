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
	sf::Vector2f game_title_pos((Settings::video_mode.width / 2.f) - (width/2.f), (Settings::video_mode.height / 2.f) - height*3);

	this->game_title.setPosition(game_title_pos);

	// new game button
	this->btn_new_game.setPosition(sf::Vector2f(game_title_pos.x+btn_new_game.getWidth()/1.5f, game_title_pos.y+300));
	this->btn_new_game.setFont(GameResources::text_font);
	this->btn_new_game.setTextColor(sf::Color::White, sf::Color::Yellow);
	this->btn_new_game.setText("Start new game");

	// settings button
	sf::Vector2f btn_ng_pos = this->btn_new_game.getPosition();

	this->btn_settings.setPosition(sf::Vector2f(btn_ng_pos.x, btn_ng_pos.y + 100));
	this->btn_settings.setFont(GameResources::text_font);
	this->btn_settings.setTextColor(sf::Color::White, sf::Color::Yellow);
	this->btn_settings.setText("Settings");

	// quit button
	sf::Vector2f btn_set_pos = this->btn_settings.getPosition();

	this->btn_quit.setPosition(sf::Vector2f(btn_set_pos.x, btn_set_pos.y + 100));
	this->btn_quit.setFont(GameResources::text_font);
	this->btn_quit.setTextColor(sf::Color::White, sf::Color::Yellow);
	this->btn_quit.setText("Quit");

	// author credit

	this->author_credit.setPosition(0, Settings::video_mode.height - 60);
	this->author_credit.setFont(GameResources::text_font);
	this->author_credit.setCharacterSize(20);
	this->author_credit.setFillColor(sf::Color(105, 105, 105));
	this->author_credit.setStyle(sf::Text::Style::Bold);
	this->author_credit.setString("author of this demo: Denis V\nemail: denisverepadev@gmail.com");

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
		try
		{
			sf::Vector2f mouse_pos(GameCycle::mouse_data.getPosition());	// get cursor position

			// update button states
			this->btn_new_game.update(mouse_pos);
			this->btn_settings.update(mouse_pos);
			this->btn_quit.update(mouse_pos);

			// handle buttons click event
			this->buttonsClickHandle();
		}
		catch (std::exception& e)
		{
			GameException ge("Menue scene logic exception!", e, GeType::Logic, __FILE__, __LINE__);
			GameLog::log(ge);
		}
	}
}

void MenueScene::buttonsClickHandle()
{
	if (this->btn_new_game.getIsClicked() && this->isEventSent == false)	// start new game
	{

	}

	if (this->btn_settings.getIsClicked() && this->isEventSent == false)	// open settings menue
	{

	}

	if (this->btn_quit.getIsClicked() && this->isEventSent == false)	// quit from game
	{
		this->isEventSent = true;
		GameCycle::addGameEvent(GameEvent::Quit); 
	}

}

void MenueScene::draw(sf::RenderTarget& target)
{
	try
	{
		// drawing game logo
		target.draw(this->game_title);
		// drawing buttons
		this->btn_new_game.draw(target);
		this->btn_settings.draw(target);
		this->btn_quit.draw(target);
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
