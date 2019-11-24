#include "GameBoard.h"
#include <iostream>

void GameBoard::createLevel() {
	static const uint16_t matrixSize = 15;
	boardVec.resize(matrixSize * matrixSize);

	for (uint16_t i = 0; i < matrixSize; i++) {
		for (uint16_t j = 0; j < matrixSize; j++) {

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
            // ice
			else if (i == 10 && j > 7 && j < 10) {
				boardVec.at(i * 15 + j) = std::make_unique<Ice>();
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
	sf::RenderWindow window(sf::VideoMode(530, 530), "Battle City - made in China (momentan)");
	window.setFramerateLimit(60);
	sf::Clock deltaClock;

	// initializam si salvam pozitia player-ului pentru a evita cautari inutile in vector sa gasim tank-ul
	uint16_t x = 13; 
	uint16_t y = 5; 

	boardVec.at(x * 15 + y) = std::make_unique<Tank>(); //deseneaza playerul in punctul initial

	while (window.isOpen())
	{
		sf::Time dt = deltaClock.restart();
		std::cout << "Last frame executed in: " << dt.asSeconds() << " seconds. \n";
		std::vector<sf::Sprite> spriteVec;
		sf::Event event;

		for (uint16_t i = 0; i < 15; i++) {
			for (uint16_t j = 0; j < 15; j++) {
				sf::Sprite tempSprite = boardVec.at(i * 15 + j)->createSprite();
				// in cazul in care este tank, avem nevoie sa rotim sprite-ul, 
				// inainte de rotatie, ca tank-ul sa nu isi modifice pozitia, origin-ul este setat in mijlocul sprite-ului, 
				// nu in coltul din stanga sus cum este by default in SFML,
				// deci vom pozitiona sprite-ul corect
				if (boardVec.at(i * 15 + j)->getType() == "tank") {

					if (((Tank*)boardVec.at(x * 15 + y).get())->getIsMoving()) {

						char direction = ((Tank*)boardVec.at(x * 15 + y).get())->getDirection();

						switch (direction) {

						case DIR_UP:

							//TODO: handle smooth movement

							((Tank*)boardVec.at(x * 15 + y).get())->setIsMoving(false);
							break;

						case DIR_DOWN:

							//TODO: handle smooth movement

							((Tank*)boardVec.at(x * 15 + y).get())->setIsMoving(false);
							break;

						case DIR_LEFT:

							//TODO: handle smooth movement

							((Tank*)boardVec.at(x * 15 + y).get())->setIsMoving(false);
							break;

						case DIR_RIGHT:

							//TODO: handle smooth movement

							((Tank*)boardVec.at(x * 15 + y).get())->setIsMoving(false);
							break;
						}

					}
					else {
						tempSprite.setPosition(TILE_SIZE * j + TILE_SIZE * 0.5, TILE_SIZE * i + TILE_SIZE * 0.5);
					}
				}

				else
					tempSprite.setPosition(TILE_SIZE * j, TILE_SIZE * i);

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
					
					switch (event.key.code) {
						case sf::Keyboard::Up : {

							((Tank*)boardVec.at(x * 15 + y).get())->setDirection(DIR_UP);

							if (boardVec.at((x - 1) * 15 + y)->getType() != "road")
								break;

							if (((Tank*)boardVec.at(x * 15 + y).get())->getIsMoving())
								break;

							((Tank*)boardVec.at(x * 15 + y).get())->setIsMoving(true);
							((Tank*)boardVec.at(x * 15 + y).get())->setFuturePosition(std::make_pair(x - 1, y));
							

							x--;
							std::swap(boardVec.at((x + 1) * 15 + y), boardVec.at(x * 15 + y));
							
							break;
						}

						case sf::Keyboard::Down: {

							((Tank*)boardVec.at(x * 15 + y).get())->setDirection(DIR_DOWN);

							if (boardVec.at((x + 1) * 15 + y)->getType() != "road")
								break;

							if (((Tank*)boardVec.at(x * 15 + y).get())->getIsMoving())
								break;

							((Tank*)boardVec.at(x * 15 + y).get())->setIsMoving(true);
							((Tank*)boardVec.at(x * 15 + y).get())->setFuturePosition(std::make_pair(x + 1, y));

							x++;
							std::swap(boardVec.at((x - 1) * 15 + y), boardVec.at(x * 15 + y));

							break;
						}

						case sf::Keyboard::Left: {

							((Tank*)boardVec.at(x * 15 + y).get())->setDirection(DIR_LEFT);

							if (boardVec.at(x * 15 + (y - 1))->getType() != "road")
								break;

							if (((Tank*)boardVec.at(x * 15 + y).get())->getIsMoving())
								break;

							((Tank*)boardVec.at(x * 15 + y).get())->setIsMoving(true);
							((Tank*)boardVec.at(x * 15 + y).get())->setFuturePosition(std::make_pair(x, y - 1));

							y--;
							std::swap(boardVec.at(x * 15 + y + 1), boardVec.at(x * 15 + y));

							break;
						}

						case sf::Keyboard::Right: {

							((Tank*)boardVec.at(x * 15 + y).get())->setDirection(DIR_RIGHT);

							if (boardVec.at(x * 15 + (y + 1))->getType() != "road")
								break;

							if (((Tank*)boardVec.at(x * 15 + y).get())->getIsMoving())
								break;

							((Tank*)boardVec.at(x * 15 + y).get())->setIsMoving(true);
							((Tank*)boardVec.at(x * 15 + y).get())->setFuturePosition(std::make_pair(x, y + 1));

							y++;
							std::swap(boardVec.at(x * 15 + y - 1), boardVec.at(x * 15 + y));

							break;
						}
					}

				}
			}

		}

		window.clear();

		// ----------------- DRAWING --------------------

		// draw game
		for (auto const& sprite : spriteVec) {
			window.draw(sprite);
		}

		window.display();
		//std::this_thread::sleep_for(std::chrono::milliseconds(1)); //TODO: de vazut daca exista vreo diferenta signifiant vizibila dpdv vizual, gpu usage mi-a scazut de la 50% la 7%
	}

}