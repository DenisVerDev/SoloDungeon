#pragma once
#include"Entity.h"

class Slime : public Entity
{

private:

	// init all animation
	virtual void initAnim();

public:

	// default constructor
	Slime();

	// update undead state
	virtual void update();
};