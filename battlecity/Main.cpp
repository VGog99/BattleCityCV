#include <SFML\Graphics.hpp>
#include <iostream>
#include "SDK.h"
#include "../Logging/Logger.h"
#include <fstream>

int main()
{
	std::ofstream logFile("log.log", std::ios::app);
	Logger logger(std::cout, Logger::Level::Info);
	logger.Log("Application started", Logger::Level::Info);
	srand(time(0));
	GameBoard game;
	game.draw();

	return 0;
}