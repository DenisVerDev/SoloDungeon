#include"../../src/headers/scenes/LevelScene.h"

//------Constructor/Destructor definition------

LevelScene::LevelScene() : GameScene()
{
	example_text.setFont(GameResources::text_font);
	example_text.setCharacterSize(64);
	example_text.setFillColor(sf::Color::Red);
	example_text.setString("GAMEPLAY IS IN PROGRESS");

	this->floor = new Floor(sf::Vector2i(160, 160));
	this->floor->setPosition(sf::Vector2f(300, 300));

	Wall w(WallType::WallFront);
	Wall w2(WallType::WallBottom);
	Wall w3(WallType::WallLeft);
	Wall w4(WallType::WallRight);

	for (int i = 0; i < 10; i++)
	{
		w.setPosition(sf::Vector2f(300 + i*16, 300 - w.getSize().y));

		w2.setPosition(sf::Vector2f(300 + i*16, 300 + this->floor->getSize().y - w2.getSize().y));

		w3.setPosition(sf::Vector2f(300 - w3.getSize().x, 300 - w.getSize().y + i * 16));

		w4.setPosition(sf::Vector2f(300+this->floor->getSize().x, 300 - w.getSize().y + i * 16));

		this->walls.push_back(w);
		this->walls.push_back(w2);
		this->walls.push_back(w3);
		this->walls.push_back(w4);
	}

	Wall w5(WallType::WallLeft_b);
	w5.setPosition(sf::Vector2f(300 - w3.getSize().x, 300 + this->floor->getSize().y - w.getSize().y));
	
	Wall w6(WallType::WallRight_b);
	w6.setPosition(sf::Vector2f(300 + this->floor->getSize().x, 300 - w.getSize().y + this->floor->getSize().y));

	Wall c1(WallType::Column);
	c1.setPosition(sf::Vector2f(340, 340));

	Wall b1(WallType::WallFlagYell);
	b1.setPosition(sf::Vector2f(316, 284));

	Wall l1(WallType::WallLava);
	l1.setPosition(sf::Vector2f(316, 300 - l1.getSize().y + l1.wall_top));

	Wall l2(WallType::WallWater);
	l2.setPosition(sf::Vector2f(340, 300 - l2.getSize().y + l2.wall_top));

	
	this->walls.push_back(w5);
	this->walls.push_back(w6);
	this->walls.push_back(c1);
	this->walls.push_back(b1);
	this->walls.push_back(l1);
	this->walls.push_back(l2);

	this->door.setPosition(sf::Vector2f(370, 300 - this->door.getSize().y));
	this->door.setState(DoorState::Closed);

	this->player = new Player();
	this->player->setPosition(sf::Vector2f(300, 300),true);

	GameLog::log("Level scene was initialized!");
}

LevelScene::~LevelScene()
{
	this->logic_thread.wait();	 // wait thread to stop
	
	delete this->floor;
	this->floor = nullptr;

	// deleting player
	delete this->player;
	this->player = nullptr;

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
	int size = this->walls.size();
	
	// logic here
	while (GameCycle::getCurrentState() == GameState::Gameplay)
	{
		for (int i = 0; i < this->walls.size(); i++)
		{
			if (this->walls[i].getWallType() == WallType::WallLava || this->walls[i].getWallType() == WallType::WallWater) this->walls[i].updateAnim();
		}
		this->player->update();

		sf::sleep(sf::milliseconds(1)); // 1000 logic call per second possible
	}
}

void LevelScene::draw(sf::RenderTarget& target)
{
	try
	{
		if (this->isLoaded == true)
		{
			this->floor->draw(target);
			for (int i = 0; i < this->walls.size(); i++)
			{
				this->walls[i].draw(target);
			}
			this->door.draw(target);
			target.draw(this->example_text);
			this->player->draw(target);
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

	this->floor->setTexture(this->levelmain_texture);
	for (int i = 0; i < this->walls.size(); i++)
	{
		this->walls[i].setTexture(this->levelmain_texture);
	}
	this->door.setTexture(this->levelmain_texture);
	this->player->setTexture(this->levelmain_texture);

	//end
	this->isLoaded = true;
	GameLog::log("Level scene resources are loaded!");
}


void LevelScene::resetEventSent()
{
	this->isEventSent = false;
}