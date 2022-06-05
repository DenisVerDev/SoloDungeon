#pragma once
#include<fstream>
#include<ctime>
#include<chrono>
#include"SFML/Window.hpp"
#include"SFML/Graphics.hpp"

//When stream doesn't read '\n' symbol -> DANGEROUS MOVE
#ifndef rEnd
#define rEnd(stream,buff) std::getline(stream, buff);
#endif 

namespace dt
{

	// Get file name from it's path
	std::string getFileName(const std::string& path);

	// Get string with date and time
	std::string getCurrentDateTime();

	// get centered position for graphical object 
	sf::Vector2f getCenteredPostion(sf::Vector2f parent_size, sf::Vector2f child_size, sf::Vector2f child_pos);

	// randomize number between min and max
	int rand(int min, int max);
}