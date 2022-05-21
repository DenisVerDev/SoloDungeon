#pragma once
#include"GameObject.h"

class Floor : public GameObject
{
	sf::Texture texture;	// floor texture is large and repeatable

public:

	//constructor with floor size
	Floor(sf::Vector2i size);

	// set floor's texture 
	virtual void setTexture(sf::Texture& texture);
};