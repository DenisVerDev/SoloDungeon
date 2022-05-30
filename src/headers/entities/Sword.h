#pragma once
#include"Player.h"
#include"SFML/Graphics.hpp"

class Player;

class Sword
{
	
private:

	//------GRAPHICAL COMPONENTS------

	sf::Sprite body;			// sword's body
	sf::IntRect texure_rect;	// body texture rect

	//------SWORD CHARACTERISTICS------

	int base_damage;					// sword's base attack damage
	float base_range;					// sword's base attack range

	float attack_speed;					// sword's swinging speed

	//------PRIVATE VARS------

	float cur_angle;					// sword's current angle
	float base_angle;					// sword's base angle
	float up_angle;						// sword's attack up angle
	float down_angle;					// sword's attack down angle

	bool rise_up;						// rise sword up
	bool rise_down;						// rise sword down

	bool attack;						// if player decided to attack
	bool attack_finished;				// if attack is finished and enemies can deal damage

	// sword's base attack animation
	void attackAnim(TurnType type);

public:

	// default constructor
	Sword();

	//------METHODS------

	// update sword's state
	void update(TurnType type);

	// start sword base attack
	void startBaseAttack();

	// bind sword to the player pos
	void bind(Player& player);

	// draw sword(without skill attack)
	void draw(sf::RenderTarget& target);

	// set sword's and skill attack effect texture
	void setTexture(sf::Texture& texture);

	//------GETTERS------

	// get sword's current damage
	int getDamage();

	// get sword's attack range
	float getRange();

	// get sword's position
	sf::Vector2f getPosition();

	// get sword's size
	sf::Vector2f getSize();

	// get if attack was finished
	bool getAttackFinish();
};