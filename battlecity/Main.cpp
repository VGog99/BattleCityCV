#include <SFML\Graphics.hpp>
#include <iostream>
#include "Steel.h"
#include "Brick.h"
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
	Brick b;
	b.setIsShootThrough();
	std::cout << b.getIsShootThrough() << "\n";
	


	return 0;
}