<<<<<<< Updated upstream
#include <SFML\Graphics.hpp>
=======
#include <iostream>
#include "SDK.h"
>>>>>>> Stashed changes


int main()
{
<<<<<<< Updated upstream
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

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
=======
	GameBoard game;
	game.draw();
>>>>>>> Stashed changes

	return 0;
}