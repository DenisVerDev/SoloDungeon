#pragma once
#include "GameObject.h"
#include"../../headers/render/Animation.h"

enum class WallType
{
	WallFront,
	WallBottom,
	WallLeft,
	WallRight,
	WallLeft_b,
	WallRight_b,
	WallFlagGreen,
	WallFlagRed,
	WallFlagBlue,
	WallFlagYell,
	WallLava,
	WallWater,
	Column
};

class Wall : public GameObject
{

private:

	WallType type;				// wall characteristics type

	Animation anim;				// wall animation

	// init wall based on it's type
	void initType();

	// initialize animation for Lava and Water
	void initAnim();

public:

	const int wall_top = 4;		// wall top

	// contructor with type and rotation initialization
	Wall(WallType type);

	virtual void draw(sf::RenderTarget& target);

	// update wall animation
	void updateAnim();

	// get wall's type
	WallType getWallType();
};