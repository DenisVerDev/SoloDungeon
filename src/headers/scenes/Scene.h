#pragma once
#include"SFML/Graphics.hpp"

/*-------------------------------------------------------------------------------------------
	Scene class:
	- ancestor of all scenes and menues
	- scene's logic handler
	- has drawing method
-------------------------------------------------------------------------------------------*/

class Scene
{
protected:

	bool isEventSent;			// if event was sent to the game cycle

	// default constructor
	Scene()
	{
		this->isEventSent = false;
	}

	// destructor => delete scene objects
	virtual ~Scene()
	{

	}

	// scene logic, you should it redefine in ancestor classes
	virtual void logic() = 0;

public:

	//------METHODS------
	
	// draw whole scene
	virtual void draw(sf::RenderTarget& target) = 0;

	// reset event sent process state
	virtual void resetEventSent()
	{
		this->isEventSent = false;
	}
};