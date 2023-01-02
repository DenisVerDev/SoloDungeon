#pragma once
#include"Enemy.h"

class Undead : public Enemy
{

private:

	// init all animation
	virtual void initAnim();

public:

	// default constructor
	Undead();
};