#include"../../src/headers/tools/DifferentTools.h"

namespace dt
{

	std::string getFileName(const std::string& path)
	{
		return path.substr(path.find_last_of("\\") + 1);
	}

	std::string getCurrentDateTime()
	{
		auto now = std::chrono::system_clock::now();
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);
		std::string time = std::ctime(&now_time);
		
		return time;
	}

}