#include"../../src/headers/gui/GameButton.h"

//------Constructor definition------

GameButton::GameButton(std::string text)
{
	this->width = 250.f;
	this->height = 40.f;

	this->isEntered = false;
	this->isClicked = false;
	this->isChecked = false;

	this->text.setFont(GameResources::text_font);
	this->text.setCharacterSize(30);
	this->text.setFillColor(GameResources::text_color);
	this->text.setString(text);
	
	this->centerTextPosition();
}

//------Methods definition------

void GameButton::update(sf::Vector2f mouse_pos)
{
	sf::Vector2f button_pos = this->getPosition();

	// check if cursor has entered
	if (this->isEntered == false && this->isMouseOver(mouse_pos, button_pos))
	{
		this->isEntered = true;
		if(this->isChecked == false) this->enterHandle();
	}
	else if(this->isEntered == true && !this->isMouseOver(mouse_pos, button_pos))
	{
		this->isEntered = false;
		if (this->isChecked == false) this->leaveHandle();
	}
	
	// check if button was pressed
	if (this->isEntered == true && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) this->isClicked = true;
	else this->isClicked = false;
}

void GameButton::loadTexture(sf::Texture& texture)
{
	this->body.setTexture(texture);
	this->body.setColor(GameResources::additional_color);
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

void GameButton::centerTextPosition()
{
	float text_width = this->text.getLocalBounds().width;
	float text_height = this->text.getLocalBounds().height;

	sf::Vector2f text_pos = dt::getCenteredPostion(sf::Vector2f(this->width, this->height), sf::Vector2f(text_width, text_height), this->position);
	this->text.setPosition(text_pos);
}

void GameButton::draw(sf::RenderTarget& target)
{
	// draw button's body
	target.draw(this->body);
	// draw button's text
	if(!this->text.getString().isEmpty()) target.draw(this->text);
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

bool GameButton::isMouseOver(sf::Vector2f mouse_pos, sf::Vector2f button_pos)
{
	return mouse_pos.x >= button_pos.x && mouse_pos.x <= button_pos.x + this->width && mouse_pos.y >= button_pos.y && mouse_pos.y <= button_pos.y + this->height;
}

//------Setters definition------

void GameButton::setPosition(sf::Vector2f position)
{
	this->position = position;
	this->body.setPosition(this->position);
	centerTextPosition();
}

void GameButton::setSize(float width, float height)
{
	this->width = width;
	this->height = height;
	this->centerTextPosition();
}

void GameButton::setText(std::string text)
{
	this->text.setString(text);
	centerTextPosition();
}


//------Getters definition------

sf::Vector2f GameButton::getPosition()
{
	return this->position;
}

bool GameButton::getIsClicked()
{
	return this->isClicked;
}

bool GameButton::getIsEntered()
{
	return this->isEntered;
}

bool GameButton::getIsChecked()
{
	return this->isChecked;
}

float GameButton::getWidth()
{
	return this->width;
}

float GameButton::getHeight()
{
	return this->height;
}
