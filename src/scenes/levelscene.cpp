#include"../../src/headers/scenes/LevelScene.h"

//------Constructor/Destructor definition------

LevelScene::LevelScene() : GameScene()
{
	// init player
	this->player = new Player();
	this->current_room = 0;

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
		// player logic
		this->player->update();

		// update rooms(animation)
		this->rooms[this->current_room]->animWalls();

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
			this->player->draw(target);

			// draw back walls and door
			this->rooms[this->current_room]->drawBackWalls(target);
			this->rooms[this->current_room]->drawBackDoor(target);
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
	this->rooms.push_back(new Room(begin_pos, RoomType::UndeadRoom));
	this->rooms.push_back(new Room(begin_pos, RoomType::OrcRoom));
	this->rooms.push_back(new Room(begin_pos, RoomType::SlimeRoom));
	this->rooms.push_back(new Room(begin_pos, RoomType::DemonRoom));
	this->rooms.push_back(new Room(begin_pos, RoomType::BossRoom));

	// init player pos
	this->rooms[this->current_room]->setEntryPoint(*this->player);
}


void LevelScene::resetEventSent()
{
	this->isEventSent = false;
}