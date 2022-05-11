#pragma once
#include"SFML/Graphics.hpp"

/*-------------------------------------------------------------------------------------------
	GameButton class:
	- simple button
	- in this game every button has the same size
	- button's texture can be divided in two different textures:
	  1) button standart texture
	  2) button mouse has entered texture
-------------------------------------------------------------------------------------------*/

class GameButton
{
private:

	//------PRIVATE VARS------	

	sf::Sprite body;			// button's graphical body
	sf::Text text;				// text over button

	bool isClicked;				// is button clicked
	bool isEntered;				// is mouse entered

	float width;				// button's width
	float height;				// button's height

	sf::Color text_color;		// text standart color
	sf::Color mover_text_color; // text button hover color

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
	GameButton(std::string text = "", sf::Text::Style style = sf::Text::Style::Regular);

	//------METHODS------

	// update button's logic
	void update(sf::Vector2f mouse_pos);

	// load button's texture
	void loadTexture(const sf::Texture& texture);

	// draw button
	void draw(sf::RenderTarget& target);

	//------SETTERS------

	// set button's position
	void setPosition(sf::Vector2f position);

	// set text label font
	void setFont(sf::Font& font);

	// set button's text
	void setText(std::string text);

	/*
		set text label color
		1) text standart color 2) text button hover color
	*/
	void setTextColor(sf::Color text_color, sf::Color mover_text_color);

	//------GETTERS------

	// get button's position
	sf::Vector2f getPosition();

	// get if button is clicked
	bool getIsClicked();

	// get if mouse has entered the button's area
	bool getIsEntered();

	float getWidth();

	float getHeight();

};