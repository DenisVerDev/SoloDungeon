#include"headers/DifferentTools.h"

std::string getFileName(const std::string& path)
{
	return path.substr(path.find_last_of("\\") + 1);
}