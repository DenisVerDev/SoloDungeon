#include"../../src/headers/gui/GameSwitch.h"

//------Constructor definition------

GameSwitch::GameSwitch() : GuiElement()
{
	this->size.x = 80.f;
	this->size.y = 35.f;

	this->body.setSize(this->size);
	this->body.setFillColor(sf::Color::Transparent);
	this->body.setOutlineThickness(1.f);
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

//------Setters definition------

void GameSwitch::setPosition(sf::Vector2f position)
{
	this->position = position;
	this->body.setPosition(this->position);
	this->centerTextPosition(this->text);
}

void GameSwitch::setSize(sf::Vector2f size)
{
	this->size = size;
	this->body.setSize(this->size);
	this->centerTextPosition(this->text);
}

void GameSwitch::setEnable(bool enable)
{
	this->isEnabled = enable;
	if (this->isEnabled == true) this->leaveHandle();
	else
	{
		this->body.setOutlineColor(GameResources::additional_color);
		this->text.setFillColor(GameResources::additional_color);
	}
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

	this->centerTextPosition(this->text);
}

//------Getters definition------

SwitchState GameSwitch::getState()
{
	return this->state;
}
