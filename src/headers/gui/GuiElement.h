#pragma once
#include"../../headers/tools/MouseData.h"
#include"../../headers/tools/DifferentTools.h"
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
	bool isEnabled;				// is gui element enabled

	sf::Vector2f size;			// gui element size

	sf::Vector2f position;		// gui element position

	//------CONSTRUCTOR------

	GuiElement()
	{
		this->isEntered = false;
		this->isClicked = false;
		this->isEnabled = true;
	}

	//------METHODS------

	// mouse enter event handler(in graphical way)
	virtual void enterHandle(){}

	// mouse leave event handler(in graphical way)
	virtual void leaveHandle(){}

	// draw gui element
	virtual void draw(sf::RenderTarget& target) = 0;

	// center text position relative to plate
	void centerTextPosition(sf::Text& text)
	{
		float text_width = text.getLocalBounds().width;
		float text_height = text.getLocalBounds().height;

		sf::Vector2f text_pos = dt::getCenteredPostion(this->size, sf::Vector2f(text_width, text_height), this->position);
		text.setPosition(sf::Vector2f(text_pos.x, text_pos.y - text_height / 2.f));
	}

	//------SETTERS------
	
	// set gui element position
	virtual void setPosition(sf::Vector2f position) = 0;

	// set gui element size
	virtual void setSize(sf::Vector2f size) = 0;

	// set gui element enable state
	virtual void setEnable(bool enable) = 0;

public:

	// update gui element logic
	virtual void update(MouseData& mouse_data)
	{
		sf::Vector2f mouse_pos(mouse_data.getPosition());

		// check if mouse has entered
		if (this->isEntered == false && this->isEnabled == true && this->isMouseOver(mouse_pos))
		{
			this->isEntered = true;
			this->enterHandle();
		}
		else if (this->isEntered == true && this->isEnabled == true && !this->isMouseOver(mouse_pos))
		{
			this->isEntered = false;
			this->leaveHandle();
		}

		this->isClicked = false;

		// check if gui element was clicked(Left button)
		if (this->isEntered == true && this->isEnabled == true && mouse_data.getIsMouseButtonPressed(sf::Mouse::Button::Left)) this->isClicked = true;
	}

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

	bool getIsEnabled()
	{
		return this->isEnabled;
	}

	// checks if mouse is over gui element
	bool isMouseOver(sf::Vector2f mouse_pos)
	{
		return mouse_pos.x >= position.x && mouse_pos.x <= position.x + size.x && mouse_pos.y >= position.y && mouse_pos.y <= position.y + size.y;
	}
};