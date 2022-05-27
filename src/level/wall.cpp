#include"../../src/headers/level/Wall.h"

Wall::Wall(WallType type)
{
	this->type = type;
	
	this->initType();
}


void Wall::initType()
{
	switch (this->type)
	{

		case WallType::WallFront:
			this->texture_rect.left = 37;
			this->texture_rect.top = 124;
			this->texture_rect.width = 16;
			this->texture_rect.height = 20;
			break;

		case WallType::WallBottom:
			this->texture_rect.left = 37;
			this->texture_rect.top = 156;
			this->texture_rect.width = 16;
			this->texture_rect.height = 20;
			break;

		case WallType::WallLeft:
			this->texture_rect.left = 32;
			this->texture_rect.top = 124;
			this->texture_rect.width = 5;
			this->texture_rect.height = 16;
			break;

		case WallType::WallLeft_b:
			this->texture_rect.left = 32;
			this->texture_rect.top = 156;
			this->texture_rect.width = 5;
			this->texture_rect.height = 20;
			break;

		case WallType::WallRight:
			this->texture_rect.left = 59;
			this->texture_rect.top = 124;
			this->texture_rect.width = 5;
			this->texture_rect.height = 16;
			break;

		case WallType::WallRight_b:
			this->texture_rect.left = 59;
			this->texture_rect.top = 156;
			this->texture_rect.width = 5;
			this->texture_rect.height = 20;
			break;

		case WallType::WallFlagGreen:
			this->texture_rect.left = 16;
			this->texture_rect.top = 48;
			this->texture_rect.width = 16;
			this->texture_rect.height = 16;
			break;

		case WallType::WallFlagRed:
			this->texture_rect.left = 16;
			this->texture_rect.top = 32;
			this->texture_rect.width = 16;
			this->texture_rect.height = 16;
			break;

		case WallType::WallFlagBlue:
			this->texture_rect.left = 32;
			this->texture_rect.top = 32;
			this->texture_rect.width = 16;
			this->texture_rect.height = 16;
			break;

		case WallType::WallFlagYell:
			this->texture_rect.left = 32;
			this->texture_rect.top = 48;
			this->texture_rect.width = 16;
			this->texture_rect.height = 20;
			break;

		case WallType::WallLava:
			this->texture_rect.left = 64;
			this->texture_rect.top = 9;
			this->texture_rect.width = 16;
			this->texture_rect.height = 27;
			this->initAnim();
			break;

		case WallType::WallWater:
			this->texture_rect.left = 64;
			this->texture_rect.top = 48;
			this->texture_rect.width = 16;
			this->texture_rect.height = 20;
			this->initAnim();
			break;

		case WallType::Column:
			this->texture_rect.left = 81;
			this->texture_rect.top = 84;
			this->texture_rect.width = 14;
			this->texture_rect.height = 35;
			break;

	}
}

void Wall::initAnim()
{
	std::vector<unsigned int> time;
	for (int i = 0; i < 3; i++)
	{
		time.push_back(Animation::ATime* 0.075);
	}
	anim.init(3, time, sf::Vector2i(this->texture_rect.left, this->texture_rect.top), true);
}

void Wall::draw(sf::RenderTarget& target)
{
	target.draw(this->body);
}

void Wall::updateAnim()
{
	this->anim.update(this->body, this->texture_rect);
}

void Wall::setType(WallType type)
{
	this->type = type;
	this->initType();
}

WallType Wall::getWallType()
{
	return this->type;
}
