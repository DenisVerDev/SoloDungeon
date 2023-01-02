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

	bool left_fixed;		// fixator for mouse left button state
	bool middle_fixed;		// fixator for mouse middle button state
	bool right_fixed;		// fixator for mouse right button state
	bool x1_fixed;			// fixator for mouse x1 button state
	bool x2_fixed;			// fixator for mouse x2 button state

public:

	//------CONSTRUCTOR------

	// default constructor
	MouseData();

	//------METHODS------

	// update mouse data from system event
	void updateData(sf::Event system_event);

	// get mouse button pressed instant state
	bool getIsMouseButtonPressed(sf::Mouse::Button button);

	//------GETTERS------

	// get mouse position in Vector2i
	sf::Vector2i getPosition();

	float getMouseWheelDelta();
};