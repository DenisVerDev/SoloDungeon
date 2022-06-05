#include"../../src/headers/gui/GameButton.h"

//------Constructor definition------

GameButton::GameButton(std::string text) : GuiElement()
{
	this->size.x = 250.f;
	this->size.y = 40.f;

	this->isChecked = false;

	this->text.setFont(GameResources::text_font);
	this->text.setCharacterSize(30);
	this->text.setFillColor(GameResources::text_color);
	this->text.setString(text);
	
	this->centerTextPosition(this->text);
}

//------Methods definition------

void GameButton::update(MouseData& mouse_data)
{
	sf::Vector2f mouse_pos(mouse_data.getPosition());

	// check if cursor has entered
	if (this->isEntered == false && this->isEnabled == true && this->isMouseOver(mouse_pos))
	{
		this->isEntered = true;
		if(this->isChecked == false) this->enterHandle();
	}
	else if(this->isEntered == true && this->isEnabled == true && !this->isMouseOver(mouse_pos))
	{
		this->isEntered = false;
		if (this->isChecked == false) this->leaveHandle();
	}
	
	this->isClicked = false;

	// check if button was clicked(Left button)
	if (this->isEntered == true && this->isEnabled == true && mouse_data.getIsMouseButtonPressed(sf::Mouse::Button::Left)) this->isClicked = true;
}

void GameButton::enterHandle()
{
	this->body.setColor(GameResources::text_color);
	this->text.setFillColor(GameResources::hover_text_color); // set text button hover color
}

void GameButton::leaveHandle()
{
	this->body.setColor(GameResources::additional_color);
	this->text.setFillColor(GameResources::text_color); // set text standart color
}

void GameButton::draw(sf::RenderTarget& target)
{
	// draw button's body
	target.draw(this->body);
	// draw button's text
	if(!this->text.getString().isEmpty()) target.draw(this->text);
}

void GameButton::loadTexture(sf::Texture& texture)
{
	this->body.setTexture(texture);
	this->body.setColor(GameResources::additional_color);
}

//------Setters definition------

void GameButton::setPosition(sf::Vector2f position)
{
	this->position = position;
	this->body.setPosition(this->position);
	centerTextPosition(this->text);
}

void GameButton::setSize(sf::Vector2f size)
{
	this->size = size;
	this->centerTextPosition(this->text);
}

void GameButton::setEnable(bool enable)
{
	this->isEnabled = enable;
	if (this->isEnabled == true) this->leaveHandle();
	else
	{
		this->body.setColor(GameResources::additional_color);
		this->text.setFillColor(GameResources::additional_color);
	}
}

void GameButton::setText(std::string text)
{
	this->text.setString(text);
	centerTextPosition(this->text);
}

void GameButton::setTextureScale(float factor_x, float factor_y)
{
	this->body.setScale(factor_x, factor_y);
}

void GameButton::setCheckMode(bool checked)
{
	this->isChecked = checked;

	if (this->isChecked == true) this->enterHandle();
	else this->leaveHandle();
}

//------Getters definition------

bool GameButton::getIsChecked()
{
	return this->isChecked;
}
