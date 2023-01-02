#pragma once
#include"../../headers/tools/ICollision.h"
#include"../../headers/render/Animation.h"
#include"../../headers/tools/AudioManager.h"
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
	Move,
	Flee,
	Hitted,
	Death
};

class Entity : public ICollision
{

protected:

	//------PRIVATE VARS------

	// graphical stuff
	sf::Sprite body;			// entity body
	sf::IntRect texture_rect;	// body texture rect

	sf::Vector2f position;		// entity position

	// animations

	Animation stand_anim;		// entity stand animation
	Animation move_anim;		// entity move animation

	// flags
	bool move_up;				// moving up flag
	bool move_down;				// moving down flag
	bool move_right;			// moving right flag
	bool move_left;				// moving left flag

	bool hasTurned;				// if entity has turned

	bool isAlive;				// if entity is alive(after all death effects)

	TurnType turn_type;			// where the entity is directed
	EntityState entity_state;	// enity action state

	// entity individual settings
	float base_speed;			// entity base speed
	float effect_speed;			// speed while hitted, death
	float speed;				// entity current speed

	float damage_range;			// entity damage range

	int health;					// entity health
	int damage;					// entity damage to other entity

	int effect_duration;		// max effect duration(hit or death effect)
	int effect_count;			// effect times count

	sf::Sound hitted;			// sound when entity gets damage

	//------PRIVATE METHODS------

	// sprite's turn handle
	virtual void turnHandle();

	// entity movement logic
	virtual void move();

	// reset entity movement logic
	virtual void resetMove();

	// update animation logic
	void updateAnim(EntityState previous_state);

	// init all animation
	virtual void initAnim();

public:

	// default constructor
	Entity();

	//------METHODS------

	// update entity state
	virtual void update();

	// attack another entity
	virtual void attack(Entity& entity);

	// get hit by another entity
	virtual void getHit(Entity& attacker);

	// processing all effects like hit, death etc.
	virtual void effectProcessing();

	// draw entity
	virtual void draw(sf::RenderTarget& target);

	// entity response to collision event
	virtual void collisionResponse(bool left, bool right, bool top, bool bottom);

	// set entity texture
	virtual void setTexture(sf::Texture& texture);

	// set entity position
	virtual void setPosition(sf::Vector2f position);

	//------GETTERS------

	// get entity position
	sf::Vector2f getPosition();

	// get entity collision size
	sf::Vector2f getSize();

	// get entity turn type
	TurnType getTurnType();

	// get entity current state
	EntityState getState();

	// get entity collision
	virtual sf::IntRect getCollision();

	// get entity attack range
	float getAttackRange();

	// get entity attack damage
	int getAttackDamage();

	// get entity current health
	int getHealth();

	// get entity live state
	bool getIsAlive();

	// if entity attacked someone(works only for the player)
	virtual bool getAttack();
};