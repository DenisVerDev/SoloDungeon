#pragma once
#include<vector>
#include"SFML/Graphics.hpp"

/*-------------------------------------------------------------------------------------------
	Animation class:
	- animation process handles in scene thread, not in the timer
	- animation speed depends on frame limit and vertical sync
-------------------------------------------------------------------------------------------*/



class Animation
{
private:

	//------PRIVATE VARS------

	unsigned int frame_count;			// count of all needed frames
	unsigned int current_frame;			// current frame in animation process

	std::vector<unsigned int> time;		// time for each frame to change 
	unsigned int current_time;			// current time since last frame change

	sf::Vector2i begin_pos;				// begining pos of the first frame

	bool isRepeated;					// will animation be repeated
	bool isEnded;						// if animation is ended

public:

	static const unsigned int ATime;	// mere of animation time(1000 milliseconds => 1 second)

	//------METHODS------

	// update time and animation
	void update(sf::Sprite& sprite, sf::IntRect& texture_rect);

	// initialize begining of the animation process(time in ATime)
	void init(unsigned int frame_count, std::vector<unsigned int> time, sf::Vector2i begin_pos, bool isRepeated = false);

	// reset current time and frame
	void reset();

	// get if animation has ended
	bool getIsEnded();
};