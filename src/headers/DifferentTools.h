#pragma once
#include<fstream>
#include<ctime>
#include<chrono>
#include"SFML/Window.hpp"

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

}