#pragma once
#include"Enemy.h"

class Slime : public Enemy
{

private:

	// init all animation
	virtual void initAnim();

public:

	// default constructor
	Slime();
};