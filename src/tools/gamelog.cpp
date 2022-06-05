#include "../../src/headers/tools/GameLog.h"

//------Initializing variables------

unsigned int GameLog::id = 1;

std::vector<std::pair<std::string, LogType>> GameLog::logs;

//------Methods definition------

void GameLog::writeLog(std::ofstream& stream,std::string text)
{
	stream << std::setw(51) << std::setfill('=') << "=\n";
	stream << "[Log id]: " << GameLog::id << ", [Date-Time]: " << dt::getCurrentDateTime();
	stream << std::setw(51) << std::setfill('-') << "-\n";
	stream << text;

	stream.flush();

	GameLog::id++;	// increasing log id
}

void GameLog::handleLogs()
{
	std::ofstream log_stream;
	std::ofstream exc_stream;

	try
	{
		log_stream.open(GameResources::log_path);
		exc_stream.open(GameResources::exc_log_path);

		while (GameCycle::running == true && log_stream.good() && exc_stream.good())
		{
			if (GameLog::logs.size() > 0)
			{
				std::string text = GameLog::logs[0].first;
				LogType type = GameLog::logs[0].second;

				GameLog::logs.erase(GameLog::logs.begin());

				switch (type)
				{
					case LogType::Log:
						GameLog::writeLog(log_stream, text);
						break;

					case LogType::Exception:
						GameLog::writeLog(exc_stream, text);
						break;
				}
			}
		}
	}
	catch (std::exception& e)
	{
		// if some exception appeares in log process => do nothing
	}

	GameLog::logs.clear();

	log_stream.close();
	exc_stream.close();
}

void GameLog::log(std::string text)
{
	GameLog::logs.push_back(std::pair<std::string, LogType>(text+"\n",LogType::Log));
}

void GameLog::log(const std::exception& e)
{
	GameLog::logs.push_back(std::pair<std::string, LogType>(e.what(), LogType::Exception));
}
