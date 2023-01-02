#pragma once
#include<exception>
#include<string>
#include<sstream>
#include<iomanip>
#include"DifferentTools.h"

/*-------------------------------------------------------------------------------------------
	Types of game exceptions:
	1) Standart - standart C++ exception
	2) Settings - exception that was caused while working with the settings
	3) Resources - exception that occures when loading resources goes bad
	4) Rendering - exception that occures during drawing process
	5) Logic - exception that occures during game scene's [update] method
	
	GameException class:
	- unites custom and standart exceptions
	- various ways of formatting exception message
-------------------------------------------------------------------------------------------*/

// game exception type
enum class GeType
{
	Standart,
	Settings,
	Resources,
	Rendering,
	Logic
};

class GameException : public std::exception
{

private:

	std::string header;					  // short main information
	std::string exception_text;			  // additional information
	std::string formatted_exception_text; // formatted exception text
	
	std::string file;					  // file where exception appeared
	int line;							  // line where exception appeared

	GeType type;	

	// get game exception type in string
	const std::string typeToString();

	// bring all data together to format exception text
	void formatExceptionText();

public:

	// create exception message without details
	GameException(std::string header, GeType type, std::string file="NONE", int line=-1);

	// create full exception message
	GameException(std::string header, std::string exception_text, GeType type, std::string file = "NONE", int line = -1);

	// create full exception message(for standart C++ exceptions)
	GameException(std::string header, const std::exception& e, GeType type, std::string file = "NONE", int line = -1);

	// create exception message without custom header(for standart C++ exceptions)
	GameException(const std::exception& e, std::string file = "NONE", int line = -1);

	// return formatted exception text
	virtual const char* what() const noexcept;
};