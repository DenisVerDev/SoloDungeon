#include "../../src/headers/level/Floor.h"

Floor::Floor(sf::Vector2i size)
{
	this->hasCollision = false;

	this->texture_rect.width = size.x;
	this->texture_rect.height = size.y;
	this->body.setTextureRect(this->texture_rect);

	this->texture.setRepeated(true);
}

void Floor::setTexture(sf::Texture& texture)
{
	sf::Image texture_img = texture.copyToImage();

	sf::Image img;
	img.create(32, 32); // constant values

	int x = 736;
	int y = 272;

	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			img.setPixel(j, i, texture_img.getPixel(x + j, y + i));
		}
	}

	this->texture.loadFromImage(img);
	this->body.setTexture(this->texture);
}


