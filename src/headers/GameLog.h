#pragma once
#include<string>
#include<exception>
#include<fstream>
#include<iomanip>
#include"DifferentTools.h"

/*-------------------------------------------------------------------------------------------
	GameLog class:
	- writes down logs to keep track of game's workflow
	- two ways to create a log:
	  1) for standart needs
	  2) for exceptions
	- private constructor => only static functions and variables
	- [id] variable for every log's type is the same
	[TODO]:1
	- log_path and exc_log_path should be in some Resource class
-------------------------------------------------------------------------------------------*/

class GameLog
{

private:

	GameLog();									// private constructor

	//------CONSTANTS------

	static const std::string log_path;			// path to file with standart logs
	static const std::string exc_log_path;		// path to log file which contains exceptions

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