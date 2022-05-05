#include"headers/DifferentTools.h"

namespace dt
{

	std::string getFileName(const std::string& path)
	{
		return path.substr(path.find_last_of("\\") + 1);
	}

}