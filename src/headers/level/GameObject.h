#pragma once
#include"../../headers/tools/ICollision.h"
#include"SFML/Graphics.hpp"

/*-------------------------------------------------------------------------------------------
	GameObject class:
	- simple static game object, like wall, decorative stuff etc.
	- size depends on texture rect
	- save to the file binary
-------------------------------------------------------------------------------------------*/

class GameObject : public ICollision
{
protected:

	//------PRIVATE VARS------

	sf::Sprite body;			// game object's body
	sf::IntRect texture_rect;	// game object's texture rect

	sf::Vector2f position;		// game object's position

public:

	//------METHODS------

	// draw game object
	virtual void draw(sf::RenderTarget& target);

	//------SETTERS------

	// set game object's position
	virtual void setPosition(sf::Vector2f position);

	// set game object bodies texture 
	virtual void setTexture(sf::Texture& texture);

	//------GETTERS------

	// get game object's position
	sf::Vector2f getPosition();

	// get game object's size
	sf::Vector2f getSize();

	// get object collision
	virtual sf::IntRect getCollision();
};