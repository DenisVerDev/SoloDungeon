#pragma once
#include<fstream>
#include"SFML/Window.hpp"

//When stream doesn't read '\n' symbol -> DANGEROUS MOVE
#ifndef rEnd
#define rEnd(stream,buff) std::getline(stream, buff);
#endif 