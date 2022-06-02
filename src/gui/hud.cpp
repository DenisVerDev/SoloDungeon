#include"../../src/headers/gui/Hud.h"

Hud::Hud(int max_health)
{
	this->max_health = max_health;

	// full heart
	this->full_rect.left = 289;
	this->full_rect.top = 258;
	this->full_rect.width = 13;
	this->full_rect.height = 12;

	this->full_heart.setTextureRect(this->full_rect);

	// empty hearth
	this->empty_rect.left = 321;
	this->empty_rect.top = 258;
	this->empty_rect.width = 13;
	this->empty_rect.height = 12;

	this->empty_heart.setTextureRect(this->empty_rect);
}

void Hud::updatePos(sf::Vector2f cam_pos, sf::Vector2f player_pos)
{
	if (this->prev_cam_pos != cam_pos)
	{
		float delta_x = 0.f;
		float delta_y = 0.f;

		if (player_pos.x > cam_pos.x) delta_x = -0.29f;
		else if (player_pos.x < cam_pos.x) delta_x = 0.29f;

		if (player_pos.y > cam_pos.y) delta_y = -0.29f;
		else if (player_pos.y < cam_pos.y) delta_y = 0.29f;

		// health bar position
		this->health_pos.x = cam_pos.x - 470.f + delta_x;
		this->health_pos.y = cam_pos.y - 260.f + delta_y;
	}
	
	// update
	this->prev_cam_pos = cam_pos;
}

void Hud::update(int health)
{
	this->health = health;
}

void Hud::draw(sf::RenderTarget& target)
{
	// draw health bar
	for (int i = 0; i < this->max_health; i++)
	{
		if (i < this->health)
		{
			this->full_heart.setPosition(sf::Vector2f(this->health_pos.x + (this->full_rect.width + 3) * i, this->health_pos.y));
			target.draw(this->full_heart);
		}
		else
		{
			this->empty_heart.setPosition(sf::Vector2f(this->health_pos.x + (this->empty_rect.width + 3) * i, this->health_pos.y));
			target.draw(this->empty_heart);
		}
	}
}

void Hud::setTexture(sf::Texture& texture)
{
	// health bar textures
	this->full_heart.setTexture(texture);
	this->empty_heart.setTexture(texture);
}
