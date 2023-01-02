#include"../../src/headers/gui/GamePlate.h"

//------Constructor definition------

GamePlate::GamePlate() : GuiElement()
{
	this->size.x = 64.f;
	this->size.y = 64.f;

	this->body.setSize(this->size);
	this->body.setFillColor(sf::Color::Transparent);
	this->body.setOutlineThickness(0.8f);
	this->body.setOutlineColor(GameResources::text_color);

	this->text.setFont(GameResources::text_font);
	this->text.setCharacterSize(24);
	this->text.setFillColor(GameResources::text_color);
}

//------Methods definition------

void GamePlate::draw(sf::RenderTarget& target)
{
	target.draw(this->body);
	target.draw(this->text);
}

//------Setters definition------

void GamePlate::setPosition(sf::Vector2f position)
{
	this->position = position;
	this->body.setPosition(this->position);
	this->centerTextPosition(this->text);
}

void GamePlate::setSize(sf::Vector2f size)
{
	this->size = size;
	this->body.setSize(size);
	this->centerTextPosition(this->text);
}

void GamePlate::setEnable(bool enable)
{
	this->isEnabled = enable;
	if (this->isEnabled == true)
	{
		this->body.setOutlineColor(GameResources::text_color);
		this->text.setFillColor(GameResources::text_color);
	}
	else
	{
		this->body.setOutlineColor(GameResources::additional_color);
		this->text.setFillColor(GameResources::additional_color);
	}
}

void GamePlate::setText(std::string text)
{
	this->text.setString(text);
	this->centerTextPosition(this->text);
}