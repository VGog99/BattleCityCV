#include <SFML\Graphics.hpp>
#include <iostream>
#include "SDK.h"

int main()
{
	srand(time(0));
	GameBoard game;
	game.draw();

	return 0;
}