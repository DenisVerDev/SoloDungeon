#include"../../src/headers/tools/MouseData.h"

//------Constructor/Destructor definition------

MouseData::MouseData()
{
	this->mouse_x = 0;
	this->mouse_y = 0;

	this->mouse_delta = 0.f;

	this->left_fixed = false;
	this->middle_fixed = false;
	this->right_fixed = false;
	this->x1_fixed = false;
	this->x2_fixed = false;
}

//------Methods definition------

void MouseData::updateData(sf::Event system_event)
{
	if (system_event.type == sf::Event::MouseMoved)
	{
		this->mouse_x = system_event.mouseMove.x;
		this->mouse_y = system_event.mouseMove.y;
		this->mouse_delta = 0.f;
	}
	else if (system_event.type == sf::Event::MouseButtonPressed || system_event.type == sf::Event::MouseButtonReleased)
	{
		this->mouse_x = system_event.mouseButton.x;
		this->mouse_y = system_event.mouseButton.y;
		this->mouse_delta = 0.f;
	}
	else if (system_event.type == sf::Event::MouseWheelScrolled)
	{
		this->mouse_x = system_event.mouseWheelScroll.x;
		this->mouse_y = system_event.mouseWheelScroll.y;
		this->mouse_delta = system_event.mouseWheelScroll.delta;
	}
}

bool MouseData::getIsMouseButtonPressed(sf::Mouse::Button button)
{
	switch (button)
	{
		case sf::Mouse::Button::Left:

			if (sf::Mouse::isButtonPressed(button) == true && this->left_fixed == false)
			{
				this->left_fixed = true;
				return true;
			}
			else if (sf::Mouse::isButtonPressed(button) == false && this->left_fixed == true) this->left_fixed = false;
			break;

		case sf::Mouse::Button::Middle:

			if (sf::Mouse::isButtonPressed(button) == true && this->middle_fixed == false)
			{
				this->middle_fixed = true;
				return true;
			}
			else if (sf::Mouse::isButtonPressed(button) == false && this->middle_fixed == true) this->middle_fixed = false;
			break;

		case sf::Mouse::Button::Right:

			if (sf::Mouse::isButtonPressed(button) == true && this->right_fixed == false)
			{
				this->right_fixed = true;
				return true;
			}
			else if (sf::Mouse::isButtonPressed(button) == false && this->right_fixed == true) this->right_fixed = false;
			break;

		case sf::Mouse::Button::XButton1:

			if (sf::Mouse::isButtonPressed(button) == true && this->x1_fixed == false)
			{
				this->x1_fixed = true;
				return true;
			}
			else if (sf::Mouse::isButtonPressed(button) == false && this->x1_fixed == true) this->x1_fixed = false;
			break;

		case sf::Mouse::Button::XButton2:

			if (sf::Mouse::isButtonPressed(button) == true && this->x2_fixed == false)
			{
				this->x2_fixed = true;
				return true;
			}
			else if (sf::Mouse::isButtonPressed(button) == false && this->x2_fixed == true) this->x2_fixed = false;
			break;

		default: break;
	}

	return false;
}

//------Getters definition------

sf::Vector2i MouseData::getPosition()
{
	sf::Vector2i position(this->mouse_x, this->mouse_y);
	return position;
}

float MouseData::getMouseWheelDelta()
{
	return this->mouse_delta;
}
