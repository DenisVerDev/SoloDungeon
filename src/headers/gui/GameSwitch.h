#pragma once
#include"GuiElement.h"
#include"../../headers/tools/GameResources.h"

/*-------------------------------------------------------------------------------------------
	GameSwitch class:
	- basic switch: ON/OFF
-------------------------------------------------------------------------------------------*/

enum class SwitchState
{
	ON,
	OFF
};

class GameSwitch : public GuiElement
{

private:

	//------PRIVATE VARS------	

	sf::RectangleShape body;	// body of the switch
	sf::Text text;				// text over switch

	SwitchState state;			// current state of the switch

	//------PRIVATE METHODS------
	
	// mouse enter event handler(in graphical way)
	virtual void enterHandle();

	// mouse leave event handler(in graphical way)
	virtual void leaveHandle();

	// set text depending on switch state
	void setText();

public:

	//------CONSTRUCTOR------
	
	// default constructor
	GameSwitch();

	//------METHODS------
	
	// handle click event
	void clickHandle();

	// draw switch
	virtual void draw(sf::RenderTarget& target);

	//------SETTERS------

	// set switch position
	virtual void setPosition(sf::Vector2f position);

	// set switch size
	virtual void setSize(sf::Vector2f size);

	// set switch enable state
	virtual void setEnable(bool enable);

	// set switch state
	void setState(SwitchState state);

	//------GETTERS------

	// get current switch state
	SwitchState getState();
};