#pragma once
#include"../../headers/tools/MouseData.h"
#include"SFML/Graphics.hpp"

/*-------------------------------------------------------------------------------------------
	GuiElement class:
	- this class is an embodyment of the standart gui element
-------------------------------------------------------------------------------------------*/

class GuiElement
{

protected:

	//------VARS------	

	bool isClicked;				// is gui element clicked
	bool isEntered;				// is mouse entered

	sf::Vector2f size;			// gui element size

	sf::Vector2f position;		// gui element position

	//------CONSTRUCTOR------

	GuiElement()
	{
		this->isEntered = false;
		this->isClicked = false;
	}

	//------METHODS------

	// update gui element logic
	virtual void update(MouseData& mouse_data)
	{
		sf::Vector2f mouse_pos(mouse_data.getPosition());

		// check if mouse has entered
		if (this->isEntered == false && this->isMouseOver(mouse_pos))
		{
			this->isEntered = true;
			this->enterHandle();
		}
		else if (this->isEntered == true && !this->isMouseOver(mouse_pos))
		{
			this->isEntered = false;
			this->leaveHandle();
		}

		this->isClicked = false;

		// check if gui element was clicked(Left button)
		if (this->isEntered == true && mouse_data.getIsMouseButtonPressed(sf::Mouse::Button::Left)) this->isClicked = true;
	}

	// mouse enter event handler(in graphical way)
	virtual void enterHandle() = 0;

	// mouse leave event handler(in graphical way)
	virtual void leaveHandle() = 0;

	// draw gui element
	virtual void draw(sf::RenderTarget& target) = 0;

	//------SETTERS------
	
	// set gui element position
	virtual void setPosition(sf::Vector2f position) = 0;

	// set gui element size
	virtual void setSize(sf::Vector2f size) = 0;

public:

	//------GETTERS------
	
	// get gui element position
	sf::Vector2f getPosition()
	{
		return this->position;
	}

	// get gui element size
	sf::Vector2f getSize()
	{
		return this->size;
	}

	// get if gui element is clicked
	bool getIsClicked()
	{
		return this->isClicked;
	}

	// get if mouse has entered the gui element area
	bool getIsEntered()
	{
		return this->isEntered;
	}

	// checks if mouse is over gui element
	bool isMouseOver(sf::Vector2f mouse_pos)
	{
		return mouse_pos.x >= position.x && mouse_pos.x <= position.x + size.x && mouse_pos.y >= position.y && mouse_pos.y <= position.y + size.y;
	}
};