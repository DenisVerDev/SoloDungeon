#pragma once
#include"Entity.h"

class Undead : public Entity
{

private:

	// init all animation
	virtual void initAnim();

public:

	// default constructor
	Undead();

	// update undead state
	virtual void update();
};