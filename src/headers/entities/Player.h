#pragma once
#include"Entity.h"

class Player : public Entity
{

private:
	sf::Texture texture;		// player's sprite sheet

	// turn sprite
	void turnHandle();

public:

	// default constructor
	Player();

	//------METHODS------

	// player behaviour logic
	virtual void behave();

	// draw player
	virtual void draw(sf::RenderTarget& target);

	// load player's sprite sheet
	void loadTexture();

};