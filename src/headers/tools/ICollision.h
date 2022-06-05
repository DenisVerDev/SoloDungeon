#pragma once
#include"SFML/Graphics.hpp"

/*-------------------------------------------------------------------------------------------
	ICollision class/interface:
	- interface that allows to check collision between two objects
-------------------------------------------------------------------------------------------*/

class ICollision
{

public:

	// mostly it's checking entity and object collision event
	// * active is the one who will react to collision event
	static void collision(ICollision& active, ICollision& passive)
	{
		sf::IntRect col_active = active.getCollision();
		sf::IntRect col_pas = passive.getCollision();

		bool left, right, top, bottom;

		// right checking - X axis
		if (col_active.left + col_active.width > col_pas.left && col_active.left + col_active.width < col_pas.left + col_pas.width)
		{
			// right checking - Y axis
			if (col_active.top >= col_pas.top && col_active.top <= col_pas.top + col_pas.height || col_active.top + col_active.height > col_pas.top && col_active.top + col_active.height <= col_pas.top + col_pas.height) right = true;
			else right = false;
		}
		else right = false;

		if (right == false)
		{
			// left checking - X axis
			if (col_active.left >= col_pas.left && col_active.left < col_pas.left + col_pas.width)
			{
				// left checking - Y axis
				if (col_active.top >= col_pas.top && col_active.top <= col_pas.top + col_pas.height || col_active.top + col_active.height > col_pas.top && col_active.top + col_active.height <= col_pas.top + col_pas.height) left = true;
				else left = false;
			}
			else left = false;
		}
		else left = false;

		// top checking - Y axis
		if (col_active.top > col_pas.top + col_pas.height/2 && col_active.top + col_active.height > col_pas.top + col_pas.height)
		{
			if (left == true || right == true) top = true;
			else top = false;
		}
		else top = false;

		// bottom checking - Y axis
		if (top == false)
		{
			if (col_active.top < col_pas.top + col_pas.height/4 && col_active.top + col_active.height > col_pas.top)
			{
				if (left == true || right == true)
				{
					bottom = true;
				}
				else bottom = false;
			}
			else bottom = false;
		}
		else bottom = false;

		if (top == true || bottom == true)
		{
			left = false;
			right = false;
		}

		active.collisionResponse(left,right,top,bottom);
	}

	// if object/entity can't move out of the certain area
	static void collision(ICollision& active, sf::IntRect area)
	{
		sf::IntRect collision = active.getCollision();

		bool left, right, top, bottom;

		// checking left
		if (collision.left < area.left) left = true;
		else left = false;

		// checking right
		if (left == false && collision.left + collision.width > area.left + area.width) right = true;
		else right = false;

		// checking top
		if (collision.top < area.top) top = true;
		else top = false;

		// checking bottom
		if (top == false && collision.top + collision.height > area.top + area.height) bottom = true;
		else bottom = false;

		active.collisionResponse(left, right, top, bottom);
	}

	// entities/objects response to collision event
	virtual void collisionResponse(bool left, bool right, bool top, bool bottom){}

	// get object or entity collision
	virtual sf::IntRect getCollision() = 0;
};