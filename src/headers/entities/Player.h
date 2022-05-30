#pragma once
#include"Entity.h"
#include"Sword.h"
#include"../../headers/render/Animation.h"
#include"../../headers/tools/GameResources.h"

/*-------------------------------------------------------------------------------------------
	Player class:
	- just a player
	- has it's own texture
	- camera manipulation
-------------------------------------------------------------------------------------------*/

class Sword;

class Player : public Entity
{

private:

	Sword* sword;				// player's main weapon

	//------PRIVATE VARS------

	float camera_radius;		// radius where camera is not allowed to move, if player is in its borders
	float camera_speed;			// camera's speed

	bool isOutOfRadius;			// if player is out of cameras effective radius

	//------ANIMATIONS------

	Animation stand_anim;		// player stand animation
	Animation move_anim;		// player move animation

	//------PRIVATE METHODS------

	// camera movement logic
	void cameraMove();

	// update animation logic
	virtual void updateAnim(EntityState previous_state);

	// init all animation
	virtual void initAnim();

public:

	// default constructor
	Player();

	// destructor => delete sword
	~Player();

	//------METHODS------

	// update player's state
	virtual void update();

	// init camera start position
	void initCamera();

	// draw player with the sword
	virtual void draw(sf::RenderTarget& target);

	// set player's and sword's textures
	virtual void setTexture(sf::Texture& texture);

	// set player's and cameras position
	void setPosition(sf::Vector2f position);
};