#pragma once
#include<fstream>
#include"SFML/Graphics.hpp"

/*-------------------------------------------------------------------------------------------
	GameObject class:
	- simple static game object, like wall, decorative stuff etc.
	- size depends on texture rect
	- save to and load from the file binary
-------------------------------------------------------------------------------------------*/

class GameObject
{
private:

	//------PRIVATE VARS------

	sf::Sprite body;			// game object's body
	sf::IntRect texture_rect;	// game object's texture rect

	sf::Vector2f position;		// game object's position

public:

	bool hasCollision;		// has game object collision

	// constructor
	GameObject(bool hasCollision = false);

	//------METHODS------

	// draw game object
	virtual void draw(sf::RenderTarget& target);

	// save game object binary
	virtual void saveObject(std::ofstream&  stream);

	// load game object binary
	virtual void loadObject(std::ifstream& stream);

	//------SETTERS------

	// set game object's position
	virtual void setPosition(sf::Vector2f position);

	// set game object bodies texture if it already has texture rect
	void setTexture(sf::Texture& texture);

	// set game object bodies texture
	void setTexture(sf::Texture& texture, const sf::IntRect rect);

	//------GETTERS------

	// get game object's position
	sf::Vector2f getPosition();

	// get game object's size
	sf::Vector2f getSize();
};