#pragma once
#include"../../headers/tools/GameResources.h"
#include"GuiElement.h"

/*-------------------------------------------------------------------------------------------
	GameSlider class
	- simple slider
-------------------------------------------------------------------------------------------*/

class GameSlider : public GuiElement
{
private:

	//------PRIVATE VARS------	

	sf::RectangleShape line;		// slider's line
	sf::Sprite circle;				// slider's circle

	sf::Text text_value;			// current value text

	float min_value;				
	float max_value;
	float current_value;

	//------PRIVATE METHODS------	
	
	// mouse enter event handler(in graphical way)
	virtual void enterHandle();

	// mouse leave event handler(in graphical way)
	virtual void leaveHandle();

	// calculate slider's value
	void calculateValue(sf::Vector2f mouse_pos);

public:

	//------CONSTRUCTOR------	

	// default constructor
	GameSlider(float min_value, float max_value, float current_value);

	//------METHODS------	

	// update slider's state
	virtual void update(MouseData& mouse_data);

	// draw slider
	virtual void draw(sf::RenderTarget& target);

	//------SETTERS------	

	void setTexture(sf::Texture& texture);

	// set slider position
	virtual void setPosition(sf::Vector2f position);

	// set slider size(this method will only change slider's width)
	virtual void setSize(sf::Vector2f size);

	// set slider enable state
	virtual void setEnable(bool enable);

	// set current value(move slider's circle)
	void setValue(float current_value);

	//------GETTERS------	

	// get current value
	float getValue();
};