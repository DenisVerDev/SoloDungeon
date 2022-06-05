#include"../../src/headers/tools/GameInput.h"

//------Initializing constants------

const int GameInput::key_actions_count = 5;
const int GameInput::mouse_actions_count = 1;

//------Initializing variables------

std::vector<std::pair<PlayerAction, sf::Keyboard::Key>> GameInput::key_actions;
std::vector<std::pair<PlayerAction, sf::Mouse::Button>> GameInput::mouse_actions;

//------Methods definition------

void GameInput::setStandartInput()
{
	GameInput::key_actions.clear();
	GameInput::mouse_actions.clear();

	// add key actions
	GameInput::key_actions.push_back(std::pair<PlayerAction, sf::Keyboard::Key>(PlayerAction::MoveUp, sf::Keyboard::Key::W));
	GameInput::key_actions.push_back(std::pair<PlayerAction, sf::Keyboard::Key>(PlayerAction::MoveDown, sf::Keyboard::Key::S));
	GameInput::key_actions.push_back(std::pair<PlayerAction, sf::Keyboard::Key>(PlayerAction::MoveRight, sf::Keyboard::Key::D));
	GameInput::key_actions.push_back(std::pair<PlayerAction, sf::Keyboard::Key>(PlayerAction::MoveLeft, sf::Keyboard::Key::A));
	GameInput::key_actions.push_back(std::pair<PlayerAction, sf::Keyboard::Key>(PlayerAction::Back, sf::Keyboard::Key::Escape));

	//	add mouse actions
	GameInput::mouse_actions.push_back(std::pair<PlayerAction, sf::Mouse::Button>(PlayerAction::Attack, sf::Mouse::Button::Left));

	GameLog::log("Game input was reseted!");

	GameInput::saveInput();
}

void GameInput::saveInput()
{
	std::ofstream ostream;

	try
	{
		ostream.open(GameResources::gameinput_path);

		if (ostream.good())
		{
			for (int i = 0; i < key_actions_count; i++)
			{
				ostream << GameInput::getActionString(GameInput::key_actions[i].first) << "=" << GameInput::key_actions[i].second << "\n";
			}

			for (int i = 0; i < mouse_actions_count; i++)
			{
				ostream << GameInput::getActionString(GameInput::mouse_actions[i].first) << "=" << GameInput::mouse_actions[i].second << "\n";
			}

			GameLog::log("Game input was successfully saved!");
		}
	}
	catch (std::exception& e)
	{
		GameException ge("Failed to save game input to file!", e, GeType::Settings, __FILE__, __LINE__);
		GameLog::log(ge);
	}

	ostream.close();
}

void GameInput::loadInput()
{
	std::ifstream istream;

	try
	{
		istream.open(GameResources::gameinput_path);

		if (istream.good())
		{
			PlayerAction action;
			std::string buff;

			for (int i = 0; i < key_actions_count; i++)
			{
				std::getline(istream, buff, '=');
				action = GameInput::getActionByName(buff);
				if(action == PlayerAction::Default) throw std::exception("There is no such PlayerAction");

				int key_id;
				istream >> key_id;
				sf::Keyboard::Key key = (sf::Keyboard::Key)key_id;
				if (key < 0) throw std::exception("There is no such key");

				GameInput::key_actions.push_back(std::pair<PlayerAction,sf::Keyboard::Key>(action,key));
				rEnd(istream, buff)
			}

			for (int i = 0; i < mouse_actions_count; i++)
			{
				std::getline(istream, buff, '=');
				action = GameInput::getActionByName(buff);
				if (action == PlayerAction::Default) throw std::exception("There is no such PlayerAction");

				int mousebtn_id;
				istream >> mousebtn_id;
				sf::Mouse::Button button = (sf::Mouse::Button)mousebtn_id;
				if (button < 0) throw std::exception("There is no such mouse button");

				GameInput::mouse_actions.push_back(std::pair<PlayerAction, sf::Mouse::Button>(action, button));
				rEnd(istream, buff)
			}

			GameLog::log("Game input was successfully loaded!");
		}
	}
	catch (std::exception& e)
	{
		GameInput::setStandartInput();

		GameException ge("Failed to load game input from file!", e, GeType::Settings, __FILE__, __LINE__);
		GameLog::log(ge);
	}

	istream.close();
}

//------Getters definition------

sf::Keyboard::Key GameInput::getKeyByAction(PlayerAction action)
{
	for (int i = 0; i < GameInput::key_actions_count; i++)
	{
		if (GameInput::key_actions[i].first == action) return GameInput::key_actions[i].second;
	}

	return sf::Keyboard::Key::KeyCount;
}

sf::Mouse::Button GameInput::getButtonByAction(PlayerAction action)
{
	for (int i = 0; i < GameInput::mouse_actions_count; i++)
	{
		if (GameInput::mouse_actions[i].first == action) return GameInput::mouse_actions[i].second;
	}

	return sf::Mouse::Button::ButtonCount;
}

PlayerAction GameInput::getActionByKey(sf::Keyboard::Key key)
{
	PlayerAction action = PlayerAction::Default;

	for (int i = 0; i < GameInput::key_actions_count; i++)
	{
		if (GameInput::key_actions[i].second == key) action = GameInput::key_actions[i].first;
	}

	return action;
}

PlayerAction GameInput::getActionByMouse(sf::Mouse::Button button)
{
	PlayerAction action = PlayerAction::Default;

	for (int i = 0; i < GameInput::mouse_actions_count; i++)
	{
		if (GameInput::mouse_actions[i].second == button) action = GameInput::mouse_actions[i].first;
	}

	return action;
}

PlayerAction GameInput::getActionByName(std::string action)
{
	if (action == "Move up") return PlayerAction::MoveUp;
	else if(action == "Move down") return PlayerAction::MoveDown;
	else if (action == "Move right") return PlayerAction::MoveRight;
	else if (action == "Move left") return PlayerAction::MoveLeft;
	else if (action == "Back") return PlayerAction::Back;
	else if (action == "Attack") return PlayerAction::Attack;

	return PlayerAction::Default;
}


std::string GameInput::getActionString(PlayerAction action)
{
	switch (action)
	{
		case PlayerAction::Default:
			return "Default";
			break;

		case PlayerAction::MoveUp:
			return "Move up";
			break;

		case PlayerAction::MoveDown:
			return "Move down";
			break;

		case PlayerAction::MoveRight:
			return "Move right";
			break;

		case PlayerAction::MoveLeft:
			return "Move left";
			break;

		case PlayerAction::Back:
			return "Back";
			break;

		case PlayerAction::Attack:
			return "Attack";
			break;
	}
}