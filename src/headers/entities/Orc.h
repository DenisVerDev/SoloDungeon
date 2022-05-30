#pragma once
#include"Entity.h"

class Orc : public Entity
{

private:

	// init all animation
	virtual void initAnim();

public:

	// default constructor
	Orc();

	// update undead state
	virtual void update();
};