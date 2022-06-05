#pragma once
#include"../../headers/tools/GameResources.h"
#include"../../headers/tools/DifferentTools.h"
#include"GuiElement.h"
#include"SFML/Graphics.hpp"

/*-------------------------------------------------------------------------------------------
	GameButton class:
	- simple button
	- button's texture can be divided in two different textures:
	  1) button standart texture
	  2) mouse has entered button's position texture
	- button's texture must be single color
-------------------------------------------------------------------------------------------*/

class GameButton : public GuiElement
{
private:

	//------PRIVATE VARS------	

	sf::Sprite body;			// button's graphical body
	sf::Text text;				// text over button

	bool isChecked;				// button check mode

	//------PRIVATE METHODS------

	// mouse enter event handler(in graphical way)
	virtual void enterHandle();

	// mouse leave event handler(in graphical way)
	virtual void leaveHandle();

public:

	//------CONSTRUCTOR------

	// public constructor
	GameButton(std::string text = "");

	//------METHODS------

	// update button's logic
	virtual void update(MouseData& mouse_data);

	// draw button
	virtual void draw(sf::RenderTarget& target);

	// load button's texture
	void loadTexture(sf::Texture& texture);

	//------SETTERS------

	// set button's position
	virtual void setPosition(sf::Vector2f position);

	// set button's size
	virtual void setSize(sf::Vector2f size);

	// set button enable state
	virtual void setEnable(bool enable);

	// set button's text
	void setText(std::string text);

	// set button's texture scale
	void setTextureScale(float factor_x, float factor_y);

	// set button's checked mode
	void setCheckMode(bool checked);

	//------GETTERS------

	// get button's check mode
	bool getIsChecked();

};