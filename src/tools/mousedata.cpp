#include"../../src/headers/tools/MouseData.h"

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
