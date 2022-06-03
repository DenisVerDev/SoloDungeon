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

	sf::Vector2f getCenteredPostion(sf::Vector2f parent, sf::Vector2f child, sf::Vector2f child_pos)
	{
		float width = (parent.x - child.x) / 2.f;
		float height = (parent.y - child.y) / 2.f;

		sf::Vector2f centered_pos(child_pos.x + width, child_pos.y + height);
		return centered_pos;
	}

	int rand(int min, int max)
	{
		double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
		int res = static_cast<int>(std::rand() * fraction * (max - min + max) + min);
		return res;
	}

}