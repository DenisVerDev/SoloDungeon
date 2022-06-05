#pragma once
#include<string>
#include<exception>
#include<fstream>
#include<iomanip>
#include"DifferentTools.h"
#include"GameResources.h"
#include"../../headers/GameCycle.h"

/*-------------------------------------------------------------------------------------------
	GameLog class:
	- writes down logs to keep track of game's workflow
	- two ways to create a log:
	  1) for standart needs
	  2) for exceptions
	- private constructor => only static functions and variables
	- [id] variable for every log's type is the same
-------------------------------------------------------------------------------------------*/

enum class LogType
{
	Log,
	Exception
};

class GameLog
{

private:

	GameLog();									// private constructor

	//------PRIVATE VARS------

	static unsigned int id;											// log id

	static std::vector<std::pair<std::string, LogType>> logs;		// all added logs

	//------PRIVATE METHODS------

	// writes log to file
	static void writeLog(std::ofstream& stream, std::string text);

public:

	//------METHODS------

	// handles all logs in different thread
	static void handleLogs();

	// create log with simple text
	static void log(std::string text);

	// create log for exceptions
	static void log(const std::exception& e);

};