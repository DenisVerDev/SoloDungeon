#include"../../src/headers/gui/GameButton.h"

//------Constructor definition------

GameButton::GameButton(std::string text, sf::Text::Style style)
{
	this->isEntered = false;
	this->isClicked = false;

	this->text.setCharacterSize(30);
	this->text.setStyle(style);
	this->text.setString(text);

	// look to the class description in the header
	this->width = 250.f;
	this->height = 40.f;
}

//------Methods definition------

void GameButton::update(sf::Vector2f mouse_pos)
{
	sf::Vector2f button_pos = this->getPosition();

	// check if cursor has entered
	if (this->isEntered == false && this->isMouseOver(mouse_pos, button_pos))
	{
		this->isEntered = true;
		this->enterHandle();
	}
	else if(this->isEntered == true && !this->isMouseOver(mouse_pos, button_pos))
	{
		this->isEntered = false;
		this->leaveHandle();
	}
	
	// check if button was pressed
	if (this->isEntered == true && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) this->isClicked = true;
	else this->isClicked = false;
}

void GameButton::loadTexture(const sf::Texture& texture)
{
	this->body.setTexture(texture);
	// set texture rect
	this->body.setTextureRect(sf::IntRect(0, 0, this->width, this->height)); // set button's standart texture
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
	this->body.setTextureRect(sf::IntRect(0, this->height, this->width, this->height)); // set button's mouse has entered texture
	this->text.setFillColor(this->mover_text_color); // set text button hover color
}

void GameButton::leaveHandle()
{
	this->body.setTextureRect(sf::IntRect(0, 0, this->width, this->height)); // set button's standart texture
	this->text.setFillColor(this->text_color); // set text standart color
}

bool GameButton::isMouseOver(sf::Vector2f mouse_pos, sf::Vector2f button_pos)
{
	return mouse_pos.x >= button_pos.x && mouse_pos.x <= button_pos.x + this->width && mouse_pos.y >= button_pos.y && mouse_pos.y <= button_pos.y + this->height;
}

//------Setters definition------

void GameButton::setPosition(sf::Vector2f position)
{
	this->body.setPosition(position);
	centerTextPosition();
}

void GameButton::setFont(sf::Font& font)
{
	this->text.setFont(font);
}

void GameButton::setText(std::string text)
{
	this->text.setString(text);
	centerTextPosition();
}

void GameButton::setTextColor(sf::Color text_color, sf::Color mover_text_color)
{
	this->text_color = text_color;
	this->mover_text_color = mover_text_color;

	this->text.setFillColor(this->text_color); // set text standart color
}

void GameButton::centerTextPosition()
{
	sf::Vector2f position = this->getPosition();

	float text_width = this->text.getLocalBounds().width;
	float text_hight = this->text.getLocalBounds().height;

	float width = (this->width-text_width) / 2.f;
	float height = (this->height-text_hight) / 2.f;

	sf::Vector2f text_pos(position.x + width, position.y + height);
	this->text.setPosition(text_pos);
}


//------Getters definition------

sf::Vector2f GameButton::getPosition()
{
	return this->body.getPosition();
}

bool GameButton::getIsClicked()
{
	return this->isClicked;
}

bool GameButton::getIsEntered()
{
	return this->isEntered;
}

float GameButton::getWidth()
{
	return this->width;
}

float GameButton::getHeight()
{
	return this->height;
}
