#pragma once
#include"GuiElement.h"
#include"../../headers/tools/GameResources.h"

/*-------------------------------------------------------------------------------------------
	GamePlate class:
	- just a square with text
	- doesnt require update and any logic
-------------------------------------------------------------------------------------------*/

class GamePlate : public GuiElement
{
private:

	//------PRIVATE VARS------	

	sf::RectangleShape body;	// body of the plate
	sf::Text text;				// text over plate

public:

	//------CONSTRUCTOR------

	// default constructor
	GamePlate();

	//------METHODS------
	
	// draw plate
	virtual void draw(sf::RenderTarget& target);

	//------SETTERS------

	// set plate position
	virtual void setPosition(sf::Vector2f position);

	// set plate size
	virtual void setSize(sf::Vector2f size);

	// set slider enable state
	virtual void setEnable(bool enable);

	// set text
	void setText(std::string text);
};