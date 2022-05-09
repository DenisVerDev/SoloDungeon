#pragma once
#include"SFML/Window.hpp"

/*-------------------------------------------------------------------------------------------
	MouseData class:
	- stores information about mouse
	- updates mouse data from system event
-------------------------------------------------------------------------------------------*/

class MouseData
{
private:

	//------PRIVATE VARS------	

	int mouse_x;			// mouse x position related to window
	int mouse_y;			// mouse y position related to window

	float mouse_delta;		// mouse wheel delta(-1 -> down, 0 -> nothing, 1 -> up)

public:

	//------METHODS------

	// update mouse data from system event
	void updateData(sf::Event system_event);

	//------GETTERS------

	// get mouse position in Vector2i
	sf::Vector2i getPosition();

	float getMouseWheelDelta();
};