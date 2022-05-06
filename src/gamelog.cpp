#include "headers/GameLog.h"

//------Initializing constants------

const std::string GameLog::log_path = "logs/logs.log";
const std::string GameLog::exc_log_path = "logs/exceptions.log";

//------Initializing variables------

unsigned int GameLog::id = 1;

std::ios::openmode GameLog::log_mode = std::ios::out;
std::ios::openmode GameLog::exc_log_mode = std::ios::out;

//------Methods definition------

void GameLog::log(std::string text)
{
	std::ofstream stream;

	try
	{
		stream.open(GameLog::log_path,GameLog::log_mode);

		if (stream.good())
		{
			stream << std::setw(51) << std::setfill('=') << "=\n";
			stream << "[Log id]: " << GameLog::id << ", [Date-Time]: " << dt::getCurrentDateTime();
			stream << std::setw(51) << std::setfill('-') << "-\n";
			stream << text << "\n";
		}
	}
	catch (std::exception& ex)
	{
		// if some exception appeares in log process => still increase id and change open mode
	}

	stream.close();

	GameLog::log_mode = std::ios::app; // change mode to append
	GameLog::id++;					   // increasing log id
}

void GameLog::log(const std::exception& e)
{
	std::ofstream stream;

	try
	{
		stream.open(GameLog::exc_log_path, GameLog::exc_log_mode);

		if (stream.good())
		{
			stream << std::setw(51) << std::setfill('=') << "=\n";
			stream << "[Log id]: " << GameLog::id << ", [Date-Time]: " << dt::getCurrentDateTime();
			stream << std::setw(51) << std::setfill('-') << "-\n";
			stream << e.what(); // don't require '\n'
		}
	}
	catch (std::exception& ex) 
	{
		// if some exception appeares in log process => still increase id and change open mode
	}

	stream.close();

	GameLog::exc_log_mode = std::ios::app; // change mode to append
	GameLog::id++;						   // increasing log id
}
