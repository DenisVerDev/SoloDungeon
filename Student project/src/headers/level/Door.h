#pragma once
#include"GameObject.h"

enum class DoorState
{
	Closed,
	Opened
};

class Door : public GameObject
{
private:

	DoorState state;	// if door is opened or closed

public:

	// default constructor
	Door();

	// set door's state
	void setState(DoorState state);

	// get door's state
	DoorState getState();
};