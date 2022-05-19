#pragma once
#include"Entity.h"
#include"../../headers/tools/GameResources.h"

/*-------------------------------------------------------------------------------------------
	Player class:
	- just a player
	- has it's own texture
	- camera manipulation
-------------------------------------------------------------------------------------------*/


class Player : public Entity
{

private:

	//------PRIVATE VARS------

	sf::Texture texture;		// player's sprite sheet

	float camera_radius;		// radius where camera is not allowed to move, if player is in its borders
	float camera_speed;			// camera's speed

	bool isOutOfRadius;			// if player is out of cameras effective radius

	//------PRIVATE METHODS------

	// camera movement logic
	void cameraMove();

public:

	// default constructor
	Player();

	//------METHODS------

	// update player's state
	virtual void update();

	// load player's sprite sheet
	void loadTexture();

	// set player's and cameras position
	void setPosition(sf::Vector2f position, bool update_camera = false);
};