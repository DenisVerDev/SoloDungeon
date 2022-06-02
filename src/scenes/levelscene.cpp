#include"../../src/headers/scenes/LevelScene.h"

//------Constructor/Destructor definition------

LevelScene::LevelScene() : GameScene()
{
	// init player
	this->player = new Player();
	this->current_room = 0;

	// init HUD
	this->hud = new Hud(this->player->getMaxHealth());

	// init other objects
	this->initLevelObjects();
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
		// update HUD
		this->hud->update(this->player->getHealth());
		this->hud->updatePos(GameRender::rview.getCenter(),this->player->getPosition());

		// player logic
		this->player->update();

		// update rooms
		this->rooms[this->current_room]->update(*this->player);

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
		}
	}
	catch (std::exception& e)
	{
		GameException ge("Levele scene drawing exception", e, GeType::Rendering, __FILE__, __LINE__);
		GameLog::log(ge);
	}

	sf::sleep(sf::milliseconds(1));
}

void LevelScene::loadResources()
{
	// load resources
	this->levelmain_texture.loadFromFile(GameResources::level_path + "mainlevbuild.png");

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


void LevelScene::resetEventSent()
{
	this->isEventSent = false;
}