#pragma once
#include<string>
#include<exception>
#include<fstream>
#include<iomanip>
#include"DifferentTools.h"
#include"GameResources.h"

/*-------------------------------------------------------------------------------------------
	GameLog class:
	- writes down logs to keep track of game's workflow
	- two ways to create a log:
	  1) for standart needs
	  2) for exceptions
	- private constructor => only static functions and variables
	- [id] variable for every log's type is the same
-------------------------------------------------------------------------------------------*/

class GameLog
{

private:

	GameLog();									// private constructor

	//------PRIVATE VARS------

	static unsigned int id;						// log id

	static std::ios::openmode log_mode;			// log file open mode
	static std::ios::openmode exc_log_mode;		// log file for exceptions open mode

public:

	//------METHODS------

	// create log with simple text
	static void log(std::string text);

	// create log for exceptions
	static void log(const std::exception& e);

};