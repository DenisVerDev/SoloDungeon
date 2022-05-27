#include "../../src/headers/level/Floor.h"

Floor::Floor()
{
	this->texture.setRepeated(true);
}

Floor::Floor(sf::Vector2i size)
{
	this->texture_rect.width = size.x;
	this->texture_rect.height = size.y;
	this->body.setTextureRect(this->texture_rect);

	this->texture.setRepeated(true);
}

void Floor::setTexture(sf::Texture& texture)
{
	sf::Image texture_img = texture.copyToImage();

	sf::Image img;
	img.create(16, 16); // constant values

	int x = 16;
	int y = 64;

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			img.setPixel(j, i, texture_img.getPixel(x + j, y + i));
		}
	}

	this->texture.loadFromImage(img);
	this->body.setTexture(this->texture);
}

void Floor::setSize(sf::Vector2i size)
{
	this->texture_rect.width = size.x;
	this->texture_rect.height = size.y;
	this->body.setTextureRect(this->texture_rect);
}


