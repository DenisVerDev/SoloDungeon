#include"../../src/headers/scenes/LevelScene.h"

//------Constructor/Destructor definition------

LevelScene::LevelScene() : GameScene()
{
	this->result = false;
	this->show_result = false;

	// init player
	this->player = new Player();
	this->current_room = 0;

	// init HUD
	this->hud = new Hud(this->player->getMaxHealth());

	// init result and tip texts
	this->result_text.setFont(GameResources::head_font);
	this->result_text.setCharacterSize(128);
	this->result_text.scale(0.5f, 0.5f);
	
	this->tip_text.setFont(GameResources::text_font);
	this->tip_text.setCharacterSize(64);
	this->tip_text.setFillColor(GameResources::text_color);
	this->tip_text.setString("Press Esc to go to the menue");
	this->tip_text.scale(0.5f, 0.5f);

	// init other objects
	this->initLevelObjects();

	this->loadResources();
	GameLog::log("Level scene was initialized!");
}

LevelScene::~LevelScene()
{
	this->logic_thread.wait();	 // wait thread to stop

	// deleting player
	delete this->player;
	this->player = nullptr;

	// deleting HUD
	delete this->hud;
	this->hud = nullptr;

	// delete rooms
	for (auto r : this->rooms)
	{
		delete r;
		r = nullptr;
	}
	this->rooms.clear();

	GameLog::log("Level scene was destroyed!");
}

//------Methods definition------

void LevelScene::start()
{
	this->logic_thread.launch();

	GameLog::log("Level scene thread has started!");
}


void LevelScene::logic()
{
	// logic here
	while (GameCycle::getCurrentState() == GameState::Gameplay && this->isEventSent == false)
	{
		try
		{
			if (!sf::Keyboard::isKeyPressed(GameInput::getKeyByAction(PlayerAction::Back)))
			{
				// update HUD
				this->hud->update(this->player->getHealth());
				this->hud->updatePos(GameRender::rview.getCenter(), this->player->getPosition());

				if (this->rooms[this->current_room]->getIsFinished() == false)
				{
					// player logic
					this->player->update();

					// update rooms
					this->rooms[this->current_room]->update(*this->player);
				}
				else if (this->current_room < 4)
				{
					GameLog::log("Player has passed " + this->rooms[this->current_room]->getRoomName());
					this->current_room++;

					// init player pos
					this->rooms[this->current_room]->setEntryPoint(*this->player);
					this->player->initCamera();
				}
				
				if(this->result == false) this->checkResult();
			}
			else
			{
				this->isEventSent = true;
				GameCycle::addGameEvent(GameEvent::SetMainMenue);
			}
		}
		catch (std::exception& e)
		{
			GameException ge("Level scene logic exception!", e, GeType::Logic, __FILE__, __LINE__);
			GameLog::log(ge);
		}

		sf::sleep(sf::milliseconds(1)); // 1000 logic call per second possible
	}
}

void LevelScene::draw(sf::RenderTarget& target)
{
	try
	{
		if (this->isLoaded == true)
		{
			// draw floor
			this->rooms[this->current_room]->drawFloor(target);

			// draw front walls and door
			this->rooms[this->current_room]->drawFrontWalls(target);
			this->rooms[this->current_room]->drawFrontDoor(target);

			// draw entities
			this->rooms[this->current_room]->drawEnemies(target);
			this->player->draw(target);

			// draw back walls and door
			this->rooms[this->current_room]->drawBackWalls(target);
			this->rooms[this->current_room]->drawBackDoor(target);

			// draw HUD
			this->hud->draw(target);

			// draw result and tip text
			if (this->show_result == true)
			{
				target.draw(this->result_text);
				target.draw(this->tip_text);
			}
		}
	}
	catch (std::exception& e)
	{
		GameException ge("Level scene drawing exception", e, GeType::Rendering, __FILE__, __LINE__);
		GameLog::log(ge);
	}

	sf::sleep(sf::milliseconds(1));
}

void LevelScene::loadResources()
{
	// load resources
	this->levelmain_texture.loadFromFile(GameResources::level_path + "mainlevbuild.png");

	AudioManager::initSound(this->lose_sound, SFXType::GameLose);
	AudioManager::initSound(this->win_sound, SFXType::GameWin);

	// player texture
	this->player->setTexture(this->levelmain_texture);

	// HUD textures
	this->hud->setTexture(this->levelmain_texture);
	
	// rooms texture set
	int vec_size = this->rooms.size();
	for (int i = 0; i < vec_size; i++)
		this->rooms[i]->setTexture(this->levelmain_texture);

	//end
	this->isLoaded = true;
	GameLog::log("Level scene resources are loaded!");
}

void LevelScene::initLevelObjects()
{
	sf::Vector2f begin_pos(Settings::video_mode.width / 2.f, Settings::video_mode.height / 2.f);

	// init rooms
	this->rooms.push_back(new RoomUndead(begin_pos));
	this->rooms.push_back(new RoomOrc(begin_pos));
	this->rooms.push_back(new RoomSlime(begin_pos));
	this->rooms.push_back(new RoomDemon(begin_pos));
	this->rooms.push_back(new RoomBoss(begin_pos));

	// init player pos
	this->rooms[this->current_room]->setEntryPoint(*this->player);
	this->player->initCamera();
}

void LevelScene::checkResult()
{
	if (this->player->getIsAlive() == false)
	{
		GameLog::log("Player has died!");
		
		this->lose_sound.play();	// play game lose sound

		this->result_text.setFillColor(sf::Color(191, 10, 48));
		this->result_text.setString("YOU ARE DEAD!");
		this->result = true;
	}
	else if (this->current_room == 4 && this->rooms[this->current_room]->getIsFinished() == true)
	{
		GameLog::log("Player has won!");
		
		this->win_sound.play();		// play game win sound

		this->result_text.setFillColor(GameResources::hover_text_color);
		this->result_text.setString("YOU HAVE WON!");
		this->result = true;
	}

	if (this->result == true)
	{
		sf::Vector2f camera = GameRender::rview.getCenter();
		sf::FloatRect res_rect, tip_rect;

		res_rect = this->result_text.getLocalBounds();
		tip_rect = this->tip_text.getLocalBounds();

		float scale = 0.5f;

		this->result_text.setPosition(sf::Vector2f(camera.x - res_rect.width / 2.f * scale, camera.y - 100));
		this->tip_text.setPosition(sf::Vector2f(camera.x - tip_rect.width / 2.f * scale, camera.y - 50 + res_rect.height*scale));

		this->show_result = true;
	}

}

void LevelScene::resetEventSent()
{
	this->isEventSent = false;
}