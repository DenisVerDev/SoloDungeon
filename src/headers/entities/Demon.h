#pragma once
#include"Entity.h"

class Demon : public Entity
{

private:

	// init all animation
	virtual void initAnim();

public:

	// default constructor
	Demon();

	// update undead state
	virtual void update();
};