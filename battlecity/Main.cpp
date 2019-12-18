#include <SFML\Graphics.hpp>
#include "Engine.h"

Engine gameEngine;

int main()
{
	std::srand(std::time(0));
	gameEngine.runGame();
	return 0;
}