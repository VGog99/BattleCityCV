#include <SFML\Graphics.hpp>
#include "Engine.h"

Engine gameEngine;

int main()
{
	std::srand(std::time(nullptr));
	gameEngine.runGame();
	return 0;
}