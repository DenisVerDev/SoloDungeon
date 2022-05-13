#pragma once
#include"../../headers/tools/GameResources.h"
#include"../../headers/tools/DifferentTools.h"
#include"SFML/Graphics.hpp"

/*-------------------------------------------------------------------------------------------
	GameButton class:
	- simple button
	- button's texture can be divided in two different textures:
	  1) button standart texture
	  2) mouse has entered button's position texture
	- button's texture must be single color
-------------------------------------------------------------------------------------------*/

class GameButton
{
private:

	//------PRIVATE VARS------	

	sf::Sprite body;			// button's graphical body
	sf::Text text;				// text over button

	bool isClicked;				// is button clicked
	bool isEntered;				// is mouse entered
	bool isChecked;				// button check mode

	float width;				// button's width
	float height;				// button's height

	sf::Vector2f position;		// button's position

	//------PRIVATE METHODS------

	// mouse enter event handler(in graphical way)
	void enterHandle();

	// mouse leave event handler(in graphical way)
	void leaveHandle();

	// center text position relative to button
	void centerTextPosition();

	// checks if mouse is over button
	bool isMouseOver(sf::Vector2f mouse_pos, sf::Vector2f button_pos);

public:

	//------CONSTRUCTOR------

	// public constructor
	GameButton(std::string text = "");

	//------METHODS------

	// update button's logic
	void update(sf::Vector2f mouse_pos);

	// draw button
	void draw(sf::RenderTarget& target);

	// load button's texture
	void loadTexture(sf::Texture& texture);

	// set button's texture scale
	void setTextureScale(float factor_x, float factor_y);

	// set button's checked mode
	void setCheckMode(bool checked);

	//------SETTERS------

	// set button's position
	void setPosition(sf::Vector2f position);

	// set button's size
	void setSize(float width, float height);

	// set button's text
	void setText(std::string text);

	//------GETTERS------

	// get button's position
	sf::Vector2f getPosition();

	// get if button is clicked
	bool getIsClicked();

	// get if mouse has entered the button's area
	bool getIsEntered();

	// get button's check mode
	bool getIsChecked();

	float getWidth();

	float getHeight();

};