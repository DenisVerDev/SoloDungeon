#pragma once
#include"SFML/Graphics.hpp"

/*-------------------------------------------------------------------------------------------
	Entity class:
	- parent class of all entities
-------------------------------------------------------------------------------------------*/

enum class TurnType	// direction in which entity is turned
{
	Left,
	Right
};

enum class EntityState	// entity action state
{
	Stand,
	Move
};

class Entity
{

protected:

	//------PRIVATE VARS------

	// graphical stuff
	sf::Sprite body;			// entity body
	sf::IntRect texture_rect;	// body texture rect

	sf::Vector2f position;		// entity position

	// flags
	bool move_up;				// moving up flag
	bool move_down;				// moving down flag
	bool move_right;			// moving right flag
	bool move_left;				// moving left flag

	bool hasTurned;				// if entity has turned
	bool hasCollision;			// if entity has collision

	TurnType turn_type;			// where the entity is directed
	EntityState entity_state;	// enity action state

	// entity individual settings
	float speed;				// entity speed

	//------PRIVATE METHODS------

	// sprite's turn handle
	virtual void turnHandle();

	// entity movement logic
	virtual void move();

	// reset entity movement logic
	virtual void resetMove();

	// update animation logic
	virtual void updateAnim(EntityState previous_state);

	// init all animation
	virtual void initAnim();

public:

	// default constructor
	Entity();

	//------METHODS------

	// update entity state
	virtual void update();

	// draw entity
	virtual void draw(sf::RenderTarget& target);

	// set entity position
	virtual void setPosition(sf::Vector2f position);

	//------GETTERS------

	// get entity position
	sf::Vector2f getPosition();

	// get entity collision size
	sf::Vector2f getSize();

};