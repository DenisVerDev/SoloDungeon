#include"../../src/headers/render/Animation.h"

//------Constants definition------

const unsigned int Animation::ATime = 1000;

//------Methods definition------

void Animation::update(sf::Sprite& sprite, sf::IntRect& texture_rect)
{
	if (this->current_frame < this->frame_count)
	{
		// set initial texture_rect
		if (this->current_time == 0 && this->current_frame == 0)
		{
			texture_rect.left = this->begin_pos.x;
			texture_rect.top = this->begin_pos.y;

			sprite.setTextureRect(texture_rect);
		}

		if (this->current_time < this->time[this->current_frame])
			this->current_time++;
		else if (this->current_time == this->time[this->current_frame])
		{
			this->current_frame++;
			this->current_time = 0;

			if (this->current_frame != this->frame_count)
			{
				// move texture rect only horizontally and width is constant
				texture_rect.left += texture_rect.width;

				sprite.setTextureRect(texture_rect);
			}
		}
	}
	else if (this->current_frame == this->frame_count)
	{
		if(this->isRepeated == true) this->reset();
		else this->isEnded = true;
	}
}

void Animation::init(unsigned int frame_count, std::vector<unsigned int> time, sf::Vector2i begin_pos, bool isRepeated)
{
	this->frame_count = frame_count;
	this->current_frame = 0;

	this->time = time;
	this->current_time = 0;

	this->begin_pos = begin_pos;

	this->isRepeated = isRepeated;
	this->isEnded = false;
}

void Animation::reset()
{
	this->current_frame = 0;
	this->current_time = 0;
	this->isEnded = false;
}

bool Animation::getIsEnded()
{
	return this->isEnded;
}
