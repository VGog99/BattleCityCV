#include <SFML\Graphics.hpp>
#include <iostream>
#include "SDK.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	Tile* testTile = new Brick();
	testTile->setCanAdvance(true);
	std::cout << testTile->getCanAdvance();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		//draw stuff

		window.display();
	}
	

	return 0;
}