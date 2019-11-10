#include <SFML\Graphics.hpp>
#include <iostream>
#include "Steel.h"
int main()
{
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
	Steel s;
	s.setIsShootThrough();
	std::cout << s.getIsShootThrough()<<"\n";


	return 0;
}