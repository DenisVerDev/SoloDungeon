#pragma once
#include"Enemy.h"

class Orc : public Enemy
{

private:

	// init all animation
	virtual void initAnim();

public:

	// default constructor
	Orc();
};