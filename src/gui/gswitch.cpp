#include"../../src/headers/gui/GameSwitch.h"

//------Constructor definition------

GameSwitch::GameSwitch()
{
	this->size.x = 80.f;
	this->size.y = 35.f;

	this->body.setSize(this->size);
	this->body.setFillColor(sf::Color::Transparent);
	this->body.setOutlineThickness(0.8f);
	this->body.setOutlineColor(GameResources::text_color);

	this->text.setFont(GameResources::text_font);
	this->text.setCharacterSize(20);
	this->text.setFillColor(GameResources::text_color);
	
	this->setState(SwitchState::ON);
}

//------Methods definition------

void GameSwitch::enterHandle()
{
	this->body.setOutlineColor(GameResources::hover_text_color);
	this->text.setFillColor(GameResources::hover_text_color);
}

void GameSwitch::leaveHandle()
{
	this->body.setOutlineColor(GameResources::text_color);
	this->text.setFillColor(GameResources::text_color);
}

void GameSwitch::clickHandle()
{
	if (this->isClicked == true)
	{
		if (this->state == SwitchState::ON) this->setState(SwitchState::OFF);
		else this->setState(SwitchState::ON);
	}
}

void GameSwitch::draw(sf::RenderTarget& target)
{
	target.draw(this->body);
	target.draw(this->text);
}

void GameSwitch::centerTextPosition()
{
	float text_width = this->text.getLocalBounds().width;
	float text_height = this->text.getLocalBounds().height;

	sf::Vector2f text_pos = dt::getCenteredPostion(this->size, sf::Vector2f(text_width, text_height), this->position);
	this->text.setPosition(sf::Vector2f(text_pos.x,text_pos.y - text_height/2.f));
}

//------Setters definition------

void GameSwitch::setPosition(sf::Vector2f position)
{
	this->position = position;
	this->body.setPosition(this->position);
	this->centerTextPosition();
}

void GameSwitch::setSize(sf::Vector2f size)
{
	this->size = size;
	this->centerTextPosition();
}

void GameSwitch::setState(SwitchState state)
{
	this->state = state;
	this->setText();
}

void GameSwitch::setText()
{
	switch (this->state)
	{
	case SwitchState::ON:
		this->text.setString("ON");
		break;

	case SwitchState::OFF:
		this->text.setString("OFF");
		break;
	}

	this->centerTextPosition();
}

//------Getters definition------

SwitchState GameSwitch::getState()
{
	return this->state;
}
