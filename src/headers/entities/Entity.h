#pragma once
#include"../../headers/tools/GameResources.h"
#include"SFML/Graphics.hpp"

/*-------------------------------------------------------------------------------------------
	Entity class:
-------------------------------------------------------------------------------------------*/

enum class TurnType
{
	Left,
	Right
};

class Entity
{

protected:

	//------PRIVATE VARS------

	sf::Sprite body;			// entity body
	sf::IntRect texture_rect;	// body texture rect
	
	bool hasCollision;			// if entity has collision

	int max_health;				// entity max health
	int current_health;			// entity current health

	int damage;					// entity damage to other entity
	int damage_radius;			// entity damage radius

	float speed;				// entity speed

	TurnType turn_type;			// where the entity is directed

	sf::Vector2f position;		// entity position

public:

	// default constructor
	Entity()
	{
		this->hasCollision = true;
		this->turn_type = TurnType::Right;
	}

	//------METHODS------
	
	// entity behaviour logic
	virtual void behave(){}

	// draw entity
	virtual void draw(sf::RenderTarget& target)
	{
		target.draw(this->body);
	}

	// set entity position
	virtual void setPosition(sf::Vector2f position)
	{
		this->position = position;
		this->body.setPosition(this->position);
	}

	//------GETTERS------

	// get entity position
	sf::Vector2f getPosition()
	{
		return this->position;
	}

	// get entity collision size
	sf::Vector2f getSize()
	{
		return sf::Vector2f(this->texture_rect.width, this->texture_rect.height);
	}

};