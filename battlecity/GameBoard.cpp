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
			// eagle + enemy + bullet(test)
			else if (i == 13 && (j == 7 || j == 9 || j == 13)) {
				if (j == 7) 
					boardVec.at(i * 15 + j) = std::make_unique<Eagle>();
				else if (j == 9)
					boardVec.at(i * 15 + j) = std::make_unique<Enemy>();
				else
					boardVec.at(i * 15 + j) = std::make_unique<Bullet>();
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

	Menu menu;
	sf::Sprite menuSprite = menu.createSprite();
	int savedMenuOption = menu.getMenuOption();


	sf::RenderWindow window(sf::VideoMode(530, 530), "Bootleg Battle City");
	window.setFramerateLimit(60);
	sf::Clock deltaClock;
	std::string tileUnderTank = "road";

	// initializam si salvam pozitia player-ului pentru a evita cautari inutile in vector sa gasim tank-ul
	uint16_t x = 13; 
	uint16_t y = 5; 

	boardVec.at(x * 15 + y) = std::make_unique<Tank>(); //deseneaza playerul in punctul initial

	while (window.isOpen())
	{

		

		sf::Time dt = deltaClock.restart();
		//std::cout << "Last frame executed in: " << dt.asSeconds() << " seconds. \n";
		std::vector<sf::Sprite> spriteVec;
		sf::Event event;

		for (uint16_t i = 0; i < 15; i++) {
			for (uint16_t j = 0; j < 15; j++) {
				sf::Sprite tempSprite = boardVec.at(i * 15 + j)->createSprite();

				if (boardVec.at(i * 15 + j)->getType() == "bullet")
				{
					tempSprite.setPosition(TILE_SIZE * j + TILE_SIZE * 0.5, TILE_SIZE * i + TILE_SIZE * 0.5);
				}
				else 

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
			
			
			if(menu.getIsInMenu())
			
			switch (event.type)
			{
				case sf::Event::Closed: {
					window.close();
					break;
				}
				case sf::Event::KeyReleased: {

					switch (event.key.code) {

					case sf::Keyboard::Up:	
						savedMenuOption = menu.getMenuOption();
						savedMenuOption++;
						savedMenuOption = std::clamp(savedMenuOption, 0, 1);
						menu.setMenuOption(savedMenuOption);
						std::cout << menu.getMenuOption();
						break;
					case sf::Keyboard::Down:
						savedMenuOption = menu.getMenuOption();
						savedMenuOption--;
						savedMenuOption = std::clamp(savedMenuOption, 0, 1);
						menu.setMenuOption(savedMenuOption);
						std::cout << menu.getMenuOption();
						break;
					case sf::Keyboard::Enter:
						break;

					}
				}
			}

			else
			
			switch (event.type) {
			case sf::Event::Closed: {
				window.close();
				break;
			}
			case sf::Event::KeyPressed: {

				switch (event.key.code) {



				case sf::Keyboard::Up: {

					((Tank*)boardVec.at(x * 15 + y).get())->setDirection(DIR_UP);

					if (boardVec.at((x - 1) * 15 + y)->getType() == "road")
					{
						if (tileUnderTank == "road")
						{
							std::swap(boardVec.at(x * 15 + y), boardVec.at((x - 1) * 15 + y));
							x--;
							tileUnderTank = "road";
						}

					}
					else
						if (boardVec.at((x - 1) * 15 + y)->getType() == "bush")
						{
							if (tileUnderTank == "bush")
							{
								std::swap(boardVec.at(x * 15 + y), boardVec.at((x - 1) * 15 + y));
								x--;
								tileUnderTank = "bush";
							}



						}
						else
							if (boardVec.at((x - 1) * 15 + y)->getType() == "ice")
							{
								if (tileUnderTank == "ice")
								{
									std::swap(boardVec.at(x * 15 + y), boardVec.at((x - 1) * 15 + y));
									x--;
									tileUnderTank = "ice";
								}


							}

					if (((Tank*)boardVec.at(x * 15 + y).get())->getIsMoving())
						break;

					((Tank*)boardVec.at(x * 15 + y).get())->setIsMoving(true);
					((Tank*)boardVec.at(x * 15 + y).get())->setFuturePosition(std::make_pair(x - 1, y));


					/*if ((boardVec.at(x * 15 + y)->getType() == "road" && boardVec.at((x - 1) * 15 + y)->getType() == "road") || (boardVec.at(x * 15 + y)->getType() == "bush" && boardVec.at((x - 1) * 15 + y)->getType() == "bush"))
					{
						std::swap(boardVec.at((x + 1) * 15 + y), boardVec.at(x * 15 + y));
						std::cout << "mere";
					}
					else
						if ((boardVec.at(x * 15 + y)->getType() == "road" && boardVec.at((x - 1) * 15 + y)->getType() == "bush") || (boardVec.at(x * 15 + y)->getType() == "bush" && boardVec.at((x - 1) * 15 + y)->getType() == "road"))
						{
							std::swap(boardVec.at((x + 1) * 15 + y), boardVec.at(x * 15 + y));
							sf::Sprite tempSprite = boardVec.at((x + 1) * 15 + y)->createSprite();
							sf::Sprite tempSprite1 = boardVec.at(x * 15 + y)->createSprite();
						}*/


					break;
				}

				case sf::Keyboard::Down: {

					((Tank*)boardVec.at(x * 15 + y).get())->setDirection(DIR_DOWN);


					if (boardVec.at((x + 1) * 15 + y)->getType() == "road")
					{
						if (tileUnderTank == "road")
						{
							std::swap(boardVec.at(x * 15 + y), boardVec.at((x + 1) * 15 + y));
							x++;
							tileUnderTank = "road";
						}

					}
					else
						if (boardVec.at((x + 1) * 15 + y)->getType() == "bush")
						{
							if (tileUnderTank == "bush")
							{
								std::swap(boardVec.at(x * 15 + y), boardVec.at((x + 1) * 15 + y));
								x++;
								tileUnderTank = "bush";
							}

						}
						else
							if (boardVec.at((x + 1) * 15 + y)->getType() == "ice")
							{
								if (tileUnderTank == "ice")
								{
									std::swap(boardVec.at(x * 15 + y), boardVec.at((x + 1) * 15 + y));
									x++;
									tileUnderTank = "ice";
								}

							}

					if (((Tank*)boardVec.at(x * 15 + y).get())->getIsMoving())
						break;

					((Tank*)boardVec.at(x * 15 + y).get())->setIsMoving(true);
					((Tank*)boardVec.at(x * 15 + y).get())->setFuturePosition(std::make_pair(x + 1, y));

					/*if (boardVec.at(x * 15 + y)->getType() == "road")
						std::swap(boardVec.at((x - 1) * 15 + y), boardVec.at(x * 15 + y));
					else
						if ((boardVec.at(x * 15 + y)->getType() == "road" && boardVec.at((x + 1) * 15 + y)->getType() == "bush") || (boardVec.at(x * 15 + y)->getType() == "bush" && boardVec.at((x + 1) * 15 + y)->getType() == "road"))
						{
							std::swap(boardVec.at((x - 1) * 15 + y), boardVec.at(x * 15 + y));
							sf::Sprite tempSprite = boardVec.at((x - 1) * 15 + y)->createSprite();
							sf::Sprite tempSprite1 = boardVec.at(x * 15 + y)->createSprite();
						}*/

					break;
				}

				case sf::Keyboard::Left: {

					((Tank*)boardVec.at(x * 15 + y).get())->setDirection(DIR_LEFT);


					if (boardVec.at(x * 15 + (y - 1))->getType() == "road")
					{
						if (tileUnderTank == "road")
						{
							std::swap(boardVec.at(x * 15 + y), boardVec.at(x * 15 + (y - 1)));
							y--;
							tileUnderTank = "road";
						}

					}
					else
						if (boardVec.at(x * 15 + (y - 1))->getType() == "bush")
						{
							if (tileUnderTank == "bush")
							{
								std::swap(boardVec.at(x * 15 + y), boardVec.at(x * 15 + (y - 1)));
								y--;
								tileUnderTank = "bush";
							}

						}
						else
							if (boardVec.at(x * 15 + (y - 1))->getType() == "ice")
							{
								if (tileUnderTank == "ice")
								{
									std::swap(boardVec.at(x * 15 + y), boardVec.at(x * 15 + (y - 1)));
									y--;
									tileUnderTank = "ice";
								}

							}

					if (((Tank*)boardVec.at(x * 15 + y).get())->getIsMoving())
						break;

					((Tank*)boardVec.at(x * 15 + y).get())->setIsMoving(true);
					((Tank*)boardVec.at(x * 15 + y).get())->setFuturePosition(std::make_pair(x, y - 1));

					/*if (boardVec.at(x * 15 + y)->getType() == "road")
						std::swap(boardVec.at(x * 15 + y + 1), boardVec.at(x * 15 + y));
					else
						if ((boardVec.at(x * 15 + y)->getType() == "road" && boardVec.at(x * 15 + (y - 1))->getType() == "bush") || (boardVec.at(x * 15 + y)->getType() == "bush" && boardVec.at(x * 15 + (y - 1))->getType() == "road"))
						{
							std::swap(boardVec.at(x * 15 + (y + 1)), boardVec.at(x * 15 + y));
							sf::Sprite tempSprite = boardVec.at(x * 15 + (y + 1))->createSprite();
							sf::Sprite tempSprite1 = boardVec.at(x * 15 + y)->createSprite();
						}*/

					break;
				}

				case sf::Keyboard::Right: {

					((Tank*)boardVec.at(x * 15 + y).get())->setDirection(DIR_RIGHT);
					if (boardVec.at(x * 15 + (y + 1))->getType() == "road")
					{

						if (tileUnderTank == "road")
						{
							std::swap(boardVec.at(x * 15 + y), boardVec.at(x * 15 + (y + 1)));
							y++;
							tileUnderTank = "road";
						}

					}
					else
						if (boardVec.at(x * 15 + (y + 1))->getType() == "bush")
						{
							if (tileUnderTank == "bush")
							{
								std::swap(boardVec.at(x * 15 + y), boardVec.at(x * 15 + (y + 1)));
								y++;
								tileUnderTank = "bush";
							}

						}
						else
							if (boardVec.at(x * 15 + (y + 1))->getType() == "ice")
							{
								if (tileUnderTank == "ice")
								{
									std::swap(boardVec.at(x * 15 + y), boardVec.at(x * 15 + (y + 1)));
									y++;
									tileUnderTank = "ice";
								}

							}

					if (((Tank*)boardVec.at(x * 15 + y).get())->getIsMoving())
						break;

					((Tank*)boardVec.at(x * 15 + y).get())->setIsMoving(true);
					((Tank*)boardVec.at(x * 15 + y).get())->setFuturePosition(std::make_pair(x, y + 1));

					/*if (boardVec.at(x * 15 + y)->getType() == "road")
						std::swap(boardVec.at(x * 15 + y - 1), boardVec.at(x * 15 + y));
					else
						if ((boardVec.at(x * 15 + y)->getType() == "road" && boardVec.at(x * 15 + (y + 1))->getType() == "bush") || (boardVec.at(x * 15 + y)->getType() == "bush" && boardVec.at(x * 15 + (y + 1))->getType() == "road"))
						{
							std::swap(boardVec.at(x * 15 + (y - 1)), boardVec.at(x * 15 + y));
							sf::Sprite tempSprite = boardVec.at(x * 15 + (y - 1))->createSprite();
							sf::Sprite tempSprite1 = boardVec.at(x * 15 + y)->createSprite();
						}*/
				}




				}
			}

			}
		}

		window.clear();

		// ----------------- DRAWING --------------------

		// draw game
		if (menu.getIsInMenu())
		{
			window.draw(menuSprite);

		}
		else
		for (auto const& sprite : spriteVec) {
			window.draw(sprite);
		}

		window.display();
		//std::this_thread::sleep_for(std::chrono::milliseconds(1)); //TODO: de vazut daca exista vreo diferenta signifiant vizibila dpdv vizual, gpu usage mi-a scazut de la 50% la 7%
	}

}