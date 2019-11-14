#include "GameBoard.h"
#include <iostream>

void GameBoard::createLevel() {
	static const int matrixSize = 15;
	boardVec.resize(matrixSize * matrixSize);

	for (unsigned int i = 0; i < matrixSize; i++) {
		for (unsigned int j = 0; j < matrixSize; j++) {
			
			// verificam daca ne aflam pe margini, daca da, vrem sa avem Steel, fiind marginile tabelei de joc
			if (i == 0 || j == 0 || i == matrixSize - 1 || j == matrixSize - 1) {
				boardVec.at(i * 15 + j) = std::make_unique<Steel>();
			}
			// niste linii de bricks for testing purposes
			else if (j % 2 == 0 && i > 1 && i < 9 ) {
				boardVec.at(i * 15 + j) = std::make_unique<Brick>();
			}
			// roads
			else {
				boardVec.at(i * 15 + j) = std::make_unique<Road>();
			}
		}
	}
}

void GameBoard::draw() {

	createLevel();
	sf::RenderWindow window(sf::VideoMode(530, 530), "Battle City");
	std::vector<sf::Sprite> spriteVec;

	// adaugam sprite-urile si setam pozitiile necesare obiectelor in spriteVec
	for (unsigned int i = 0; i < 15; i++) {
		for (unsigned int j = 0; j < 15; j++) {
			sf::Sprite tempSprite = boardVec.at(i * 15 + j)->createSprite();
			tempSprite.setPosition(float(35 * j), float(35 * i));
			spriteVec.emplace_back(tempSprite);
		}
	}

	while (window.isOpen())
	{
		sf::Event event;
		Player player;
		while (window.pollEvent(event))
		{

			switch (event.type) {
				case sf::Event::Closed: {
					window.close();
					break;
				}

				case sf::Event::KeyPressed: {
					
					switch (event.key.code) {
						case sf::Keyboard::Up : {
							player.setDirection('0');
							std::cout << player.getDirection();
							break;
						}

						case sf::Keyboard::Down: {
							player.setDirection('1');
							std::cout << player.getDirection();
							break;
						}

						case sf::Keyboard::Left: {
							player.setDirection('2');
							std::cout << player.getDirection();
							break;
						}

						case sf::Keyboard::Right: {
							player.setDirection('3');
							std::cout << player.getDirection();
							break;
						}
					}

				}
			}

		}

		window.clear();

		//draw stuff

		//level drawing
		for (auto const& sprite : spriteVec) {
			window.draw(sprite);
		}

		window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(1)); //TODO: de vazut daca exista vreo diferenta signifiant vizibila dpdv vizual, gpu usage mi-a scazut de la 50% la 7%
	}

}