#include "GameBoard.h"
#include <iostream>

void GameBoard::createLevel() {
	static const int matrixSize = 15;
	boardVec.resize(matrixSize * matrixSize);

	for (unsigned int i = 0; i < matrixSize; i++) {
		for (unsigned int j = 0; j < matrixSize; j++) {

			// din pacate nu exista switch cu mai multe argumente, deci o sa avem un trenulet de ifs

			// verificam daca ne aflam pe margini, daca da, vrem sa avem Steel, fiind marginile tabelei de joc
			if (i == 0 || j == 0 || i == matrixSize - 1 || j == matrixSize - 1) {
				boardVec.at(i * 15 + j) = std::make_unique<Steel>();
			}
			// niste linii de bricks for testing purposes
			else if (j % 2 == 0 && i > 1 && i < 9 ) {
				boardVec.at(i * 15 + j) = std::make_unique<Brick>();
			}
			// tufisuri 
			else if (i == 11 && j > 4 && j < 9 ) {
				boardVec.at(i * 15 + j) = std::make_unique<Bush>();
			}
			// apa
			else if (i == 10 && j > 4 && j < 8) {
				boardVec.at(i * 15 + j) = std::make_unique<Water>();
			}
			// eagle + enemy
			else if (i == 13 && (j == 7 || j == 9)) {
				if (j == 7) 
					boardVec.at(i * 15 + j) = std::make_unique<Eagle>();
				else
					boardVec.at(i * 15 + j) = std::make_unique<Enemy>();

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

	int x = 13; //pozitia x initiala a playerului
	int y = 5; //pozitia y initiala a playerului

	boardVec.at(x * 15 + y) = std::make_unique<Player>();  //deseneaza playerul in punctul initial

	while (window.isOpen())
	{
		sf::Event event;
		Player player;

		for (unsigned int i = 0; i < 15; i++) {
			for (unsigned int j = 0; j < 15; j++) {
				sf::Sprite tempSprite = boardVec.at(i * 15 + j)->createSprite();
				tempSprite.setPosition(float(35 * j), float(35 * i));
				spriteVec.emplace_back(tempSprite);
			}
		}

		while (window.pollEvent(event))
		{

			switch (event.type) {
				case sf::Event::Closed: {
					window.close();
					break;
				}

				case sf::Event::KeyPressed: {
					
					// ghetto moving, de facut ceva mai inteligent, will do for now

					switch (event.key.code) {
						case sf::Keyboard::Up : {

							player.setDirection('0');

							boardVec.at(x * 15 + y) = std::make_unique<Road>();
							x--;
								
							if (boardVec.at(x * 15 + y)->getType() == "road")
								boardVec.at(x * 15 + y) = std::make_unique<Player>();  //playerul urca
							
							break;
						}

						case sf::Keyboard::Down: {
							player.setDirection('1');

							boardVec.at(x * 15 + y) = std::make_unique<Road>();
							x++;
							
							if (boardVec.at(x * 15 + y)->getType() == "road")
								boardVec.at(x * 15 + y) = std::make_unique<Player>();  //playerul coboara

							break;
						}

						case sf::Keyboard::Left: {
							player.setDirection('2');

							boardVec.at(x * 15 + y) = std::make_unique<Road>();
							y--;

							if (boardVec.at(x * 15 + y)->getType() == "road")
								boardVec.at(x * 15 + y) = std::make_unique<Player>();  //playerul se muta la stanga

							break;
						}

						case sf::Keyboard::Right: {
							player.setDirection('3');

							boardVec.at(x * 15 + y) = std::make_unique<Road>();
							y++;

							if (boardVec.at(x * 15 + y)->getType() == "road")
								boardVec.at(x * 15 + y) = std::make_unique<Player>();  //playerul se muta la dreapta

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
		//std::this_thread::sleep_for(std::chrono::milliseconds(1)); //TODO: de vazut daca exista vreo diferenta signifiant vizibila dpdv vizual, gpu usage mi-a scazut de la 50% la 7%
	}

}