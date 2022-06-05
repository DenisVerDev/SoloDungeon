#pragma once
#include"SFML/Graphics.hpp"

/*-------------------------------------------------------------------------------------------
	Hud class:
	- shows health bar in the top-left corner of the window
-------------------------------------------------------------------------------------------*/

class Hud
{

private:

	sf::Vector2f prev_cam_pos;	// previous camera position

	//------HEALTHBAR COMPONENTS------

	sf::Sprite full_heart;		// full heart body
	sf::Sprite empty_heart;		// empty heart body

	sf::IntRect full_rect;
	sf::IntRect empty_rect;

	sf::Vector2f health_pos;	// health bar position

	int max_health;				// player's max health
	int health;					// player's current helth

public:

	// constructor
	Hud(int max_health);

	// update hud elements positions
	void updatePos(sf::Vector2f cam_pos, sf::Vector2f player_pos);

	// update all data
	void update(int health);

	// draw player's hud
	void draw(sf::RenderTarget& target);

	// set texture to all components
	void setTexture(sf::Texture& texture);
};