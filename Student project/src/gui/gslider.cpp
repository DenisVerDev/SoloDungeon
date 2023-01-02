#include"../../src/headers/gui/GameSlider.h"

//------Constructor------

GameSlider::GameSlider(float min_value, float max_value, float current_value) : GuiElement()
{
	this->min_value = min_value;
	this->max_value = max_value;
	this->current_value = current_value;

	this->size.x = 300.f;
	this->size.y = 20.f;

	this->line.setSize(sf::Vector2f(this->size.x, 1.f));
	this->line.setFillColor(GameResources::text_color);

	this->circle.setColor(GameResources::text_color);

	this->text_value.setFont(GameResources::text_font);
	this->text_value.setCharacterSize(22);
	this->text_value.setFillColor(GameResources::text_color);
}

//------Methods definition------

void GameSlider::update(MouseData& mouse_data)
{
	sf::Vector2f mouse_pos(mouse_data.getPosition());

	// check if mouse has entered
	if (this->isEntered == false && this->isEnabled == true && this->isMouseOver(mouse_pos))
	{
		this->isEntered = true;
		this->enterHandle();
	}
	else if (this->isEntered == true && this->isEnabled == true && !this->isMouseOver(mouse_pos))
	{
		this->isEntered = false;
		this->leaveHandle();
	}

	this->isClicked = false;

	// check if the mouse button was pressed
	if (this->isEntered == true && this->isEnabled == true && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		this->isClicked = true;
		this->calculateValue(mouse_pos);
	}
}

void GameSlider::enterHandle()
{
	this->circle.setColor(GameResources::hover_text_color);
}

void GameSlider::leaveHandle()
{
	this->circle.setColor(GameResources::text_color);
}

void GameSlider::calculateValue(sf::Vector2f mouse_pos)
{
	this->circle.setPosition(sf::Vector2f(mouse_pos.x - this->circle.getLocalBounds().width/2.f, this->circle.getPosition().y));

	float relative_pos = mouse_pos.x - this->position.x;
	float percent_pos = (relative_pos * 100.f) / this->size.x;

	float real_max_value = this->max_value - this->min_value;

	float real_value = (real_max_value * percent_pos) / 100.f;
	this->current_value = this->min_value + real_value;

	this->text_value.setString(std::to_string((int)this->current_value));
}

void GameSlider::draw(sf::RenderTarget& target)
{
	target.draw(this->line);
	target.draw(this->circle);
	target.draw(this->text_value);
}

//------Setters definition------

void GameSlider::setTexture(sf::Texture& texture)
{
	this->circle.setTexture(texture);
}

void GameSlider::setPosition(sf::Vector2f position)
{
	this->position = position;

	this->line.setPosition(sf::Vector2f(this->position.x, this->position.y + this->circle.getLocalBounds().width / 2.f));
	this->circle.setPosition(sf::Vector2f(this->position.x, this->position.y));
	this->setValue(this->current_value);

	float text_height = this->text_value.getLocalBounds().height;
	this->text_value.setPosition(sf::Vector2f(this->position.x + this->line.getLocalBounds().width + 30.f,this->position.y + this->circle.getLocalBounds().width / 2.f - text_height));
}

void GameSlider::setSize(sf::Vector2f size)
{
	this->size.x = size.x;
	this->line.setSize(sf::Vector2f(this->size.x, 1.f));
	this->setPosition(this->position);	// reset elements positions due to size change
}

void GameSlider::setEnable(bool enable)
{
	this->isEnabled = enable;
	if (this->isEnabled == true)
	{
		this->line.setFillColor(GameResources::text_color);
		this->circle.setColor(GameResources::text_color);
	}
	else
	{
		this->line.setFillColor(GameResources::additional_color);
		this->circle.setColor(GameResources::additional_color);
	}
}

void GameSlider::setValue(float current_value)
{
	if (current_value >= this->min_value && current_value <= this->max_value) this->current_value = current_value;
	else this->current_value = this->min_value;

	float real_max_value = this->max_value - this->min_value;
	float real_value = this->current_value - this->min_value;

	float value_percent = (real_value * 100.f) / real_max_value;

	float circle_x = (this->size.x * value_percent) / 100.f;

	this->circle.setPosition(sf::Vector2f(this->position.x + circle_x - this->circle.getLocalBounds().width / 2.f, this->circle.getPosition().y));

	this->text_value.setString(std::to_string((int)this->current_value));
}

//------Getters definition------

float GameSlider::getValue()
{
	return this->current_value;
}
