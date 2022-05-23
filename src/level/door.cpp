#include"../../src/headers/level/Door.h"

Door::Door()
{
	this->hasCollision = true;
	this->setState(DoorState::Closed);
}

void Door::setState(DoorState state)
{
	switch (state)
	{
		case DoorState::Closed:
			this->texture_rect.left = 16;
			this->texture_rect.top = 221;
			this->texture_rect.width = 64;
			this->texture_rect.height = 35;
			break;

		case DoorState::Opened:
			this->texture_rect.left = 16;
			this->texture_rect.top = 260;
			this->texture_rect.width = 64;
			this->texture_rect.height = 35;
			break;
	}
}
