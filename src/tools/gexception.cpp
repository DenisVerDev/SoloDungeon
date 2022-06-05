#include"../../src/headers/tools/GameException.h"

//------Constructors definition------

GameException::GameException(std::string header, GeType type, std::string file, int line)
{
	if (!header.empty()) this->header = header;
	else this->header = "Header is empty!";

	this->type = type;

	if (file.find_last_of('\\') != std::string::npos) this->file = dt::getFileName(file);
	else this->file = "NONE";

	this->line = line;

	this->formatExceptionText();
}

GameException::GameException(std::string header, std::string exception_text, GeType type, std::string file, int line)
{
	if (!header.empty()) this->header = header;
	else this->header = "Header is empty!";

	if (!exception_text.empty()) this->exception_text = exception_text;
	else this->exception_text = "No additional information";

	this->type = type;

	if (file.find_last_of('\\') != std::string::npos) this->file = dt::getFileName(file);
	else this->file = "NONE";

	this->line = line;

	this->formatExceptionText();
}

GameException::GameException(std::string header, const std::exception& e, GeType type, std::string file, int line)
{
	if (!header.empty()) this->header = header;
	else this->header = "Header is empty!";

	this->exception_text = e.what();

	this->type = type;

	if (file.find_last_of('\\') != std::string::npos) this->file = dt::getFileName(file);
	else this->file = "NONE";

	this->line = line;

	this->formatExceptionText();
}

GameException::GameException(const std::exception& e, std::string file, int line)
{
	this->header = "Standart exception";

	this->exception_text = e.what();

	this->type = GeType::Standart;

	if (file.find_last_of('\\') != std::string::npos) this->file = dt::getFileName(file);
	else this->file = "NONE";

	this->line = line;

	this->formatExceptionText();
}

//------Methods definition------

const std::string GameException::typeToString()
{
	switch (this->type)
	{
		case GeType::Standart:
			return "Standart";
			break;

		case GeType::Settings:
			return "Settings";
			break;

		case GeType::Resources:
			return "Resources";
			break;

		case GeType::Rendering:
			return "Rendering";
			break;

		case GeType::Logic:
			return "Logic";
			break;

		default: return "Standart";
	}
}

void GameException::formatExceptionText()
{
	std::ostringstream stream;

	if (this->file != "NONE" && this->line > 0) stream << '[' << this->typeToString() << "] File: " << this->file << ", Line: " << this->line << "\n";
	else stream << '[' << this->typeToString() << "]:" << "\n";

	stream << "-HEADER: " << this->header << "\n";
	if (!this->exception_text.empty()) stream << "-INFO: " << this->exception_text << "\n";

	this->formatted_exception_text = stream.str();
}

const char* GameException::what() const noexcept
{
	return this->formatted_exception_text.c_str();
}
