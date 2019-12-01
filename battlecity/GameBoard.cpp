#include "GameBoard.h"
#include <iostream>
#include <fstream>

void GameBoard::createLevel() {

	int inputFromFile;

	std::ifstream file("../stages/stage1.txt");
	boardVec.resize(MATRIX_SIZE * MATRIX_SIZE);

	for (uint16_t i = 0; i < MATRIX_SIZE; i++) {
		for (uint16_t j = 0; j < MATRIX_SIZE; j++) {

			file >> inputFromFile;

			switch (inputFromFile) {

			case 1:

				boardVec.at(i * MATRIX_SIZE + j) = std::make_unique<Steel>();
				break;

			case 2:

				boardVec.at(i * MATRIX_SIZE + j) = std::make_unique<Brick>();
				break;

			case 3:

				boardVec.at(i * MATRIX_SIZE + j) = std::make_unique<Eagle>();
				break;

			case 4:

				boardVec.at(i * MATRIX_SIZE + j) = std::make_unique<Tank>();
				playerPosX = i;
				playerPosY = j;
				break;

			case 5:

				boardVec.at(i * MATRIX_SIZE + j) = std::make_unique<Enemy>();
				enemyPosX = i;
				enemyPosY = j;
				break;

			case 6:

				boardVec.at(i * MATRIX_SIZE + j) = std::make_unique<Bush>();
				break;

			default:

				boardVec.at(i * MATRIX_SIZE + j) = std::make_unique<Road>();
				break;

			}

		}
	}
}

	




void GameBoard::enemyLogic() {

	//update la pozitia enemy la 0.5 secunde
	lastMoveTime += dt;
	if (lastMoveTime.asSeconds() >= 0.5) {

		char direction = Enemy::randomMovement();

		switch (direction) {
		case DIR_UP:

			((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setDirection(DIR_UP);

			if (boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY)->getType() == "road")
			{
				std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY));
				enemyPosX--;
			}

			break;

		case DIR_DOWN:

			((Enemy*)boardVec.at(enemyPosX * 15 + enemyPosY).get())->setDirection(DIR_DOWN);

			if (boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY)->getType() == "road")
			{
				std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY));
				enemyPosX++;
			}

			break;

		case DIR_LEFT:

			((Enemy*)boardVec.at(enemyPosX * 15 + enemyPosY).get())->setDirection(DIR_LEFT);

			if (boardVec.at((enemyPosX)* MATRIX_SIZE + enemyPosY - 1)->getType() == "road")
			{
				std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX)* MATRIX_SIZE + enemyPosY - 1));
				enemyPosY--;
			}

			break;

		case DIR_RIGHT:

			((Enemy*)boardVec.at(enemyPosX * 15 + enemyPosY).get())->setDirection(DIR_RIGHT);

			if (boardVec.at((enemyPosX)* MATRIX_SIZE + enemyPosY + 1)->getType() == "road")
			{
				std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX)* MATRIX_SIZE + enemyPosY + 1));
				enemyPosY++;
			}
			break;
		}

		lastMoveTime = sf::seconds(0);
	}
}

void GameBoard::playerLogic() {



}

void GameBoard::executeOnKeyUp() {

	((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setDirection(DIR_UP);

	if (boardVec.at((playerPosX - 1) * 15 + playerPosY)->getType() == "road")
	{
		if (tileUnderTank == "road")
		{
			std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX - 1) * 15 + playerPosY));
			playerPosX--;
			tileUnderTank = "road";
		}

	}
	else
		if (boardVec.at((playerPosX - 1) * 15 + playerPosY)->getType() == "bush")
		{
			if (tileUnderTank == "bush")
			{
				std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX - 1) * 15 + playerPosY));
				playerPosX--;
				tileUnderTank = "bush";
			}



		}
		else
			if (boardVec.at((playerPosX - 1) * 15 + playerPosY)->getType() == "ice")
			{
				if (tileUnderTank == "ice")
				{
					std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX - 1) * 15 + playerPosY));
					playerPosX--;
					tileUnderTank = "ice";
				}


			}

	if (((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->getIsMoving())
		return;
	
	((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsMoving(true);
	((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setFuturePosition(std::make_pair(playerPosX - 1, playerPosY));
}

void GameBoard::executeOnKeyDown() {
	((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setDirection(DIR_DOWN);


	if (boardVec.at((playerPosX + 1) * 15 + playerPosY)->getType() == "road")
	{
		if (tileUnderTank == "road")
		{
			std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX + 1) * 15 + playerPosY));
			playerPosX++;
			tileUnderTank = "road";
		}

	}
	else
		if (boardVec.at((playerPosX + 1) * 15 + playerPosY)->getType() == "bush")
		{
			if (tileUnderTank == "bush")
			{
				std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX + 1) * 15 + playerPosY));
				playerPosX++;
				tileUnderTank = "bush";
			}

		}
		else
			if (boardVec.at((playerPosX + 1) * 15 + playerPosY)->getType() == "ice")
			{
				if (tileUnderTank == "ice")
				{
					std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX + 1) * 15 + playerPosY));
					playerPosX++;
					tileUnderTank = "ice";
				}

			}

	if (((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->getIsMoving())
		return;

	((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsMoving(true);
	((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setFuturePosition(std::make_pair(playerPosX + 1, playerPosY));
}

void GameBoard::executeOnKeyLeft() {
	((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setDirection(DIR_LEFT);


	if (boardVec.at(playerPosX * 15 + (playerPosY - 1))->getType() == "road")
	{
		if (tileUnderTank == "road")
		{
			std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY - 1)));
			playerPosY--;
			tileUnderTank = "road";
		}

	}
	else
		if (boardVec.at(playerPosX * 15 + (playerPosY - 1))->getType() == "bush")
		{
			if (tileUnderTank == "bush")
			{
				std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY - 1)));
				playerPosY--;
				tileUnderTank = "bush";
			}

		}
		else
			if (boardVec.at(playerPosX * 15 + (playerPosY - 1))->getType() == "ice")
			{
				if (tileUnderTank == "ice")
				{
					std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY - 1)));
					playerPosY--;
					tileUnderTank = "ice";
				}

			}

	if (((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->getIsMoving())
		return;

	((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsMoving(true);
	((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setFuturePosition(std::make_pair(playerPosX, playerPosY - 1));
}

void GameBoard::executeOnKeyRight() {
	((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setDirection(DIR_RIGHT);
	if (boardVec.at(playerPosX * 15 + (playerPosY + 1))->getType() == "road")
	{

		if (tileUnderTank == "road")
		{
			std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY + 1)));
			playerPosY++;
			tileUnderTank = "road";
		}

	}
	else
		if (boardVec.at(playerPosX * 15 + (playerPosY + 1))->getType() == "bush")
		{
			if (tileUnderTank == "bush")
			{
				std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY + 1)));
				playerPosY++;
				tileUnderTank = "bush";
			}

		}
		else
			if (boardVec.at(playerPosX * 15 + (playerPosY + 1))->getType() == "ice")
			{
				if (tileUnderTank == "ice")
				{
					std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY + 1)));
					playerPosY++;
					tileUnderTank = "ice";
				}

			}

	if (((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->getIsMoving())
		return;

	((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsMoving(true);
	((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setFuturePosition(std::make_pair(playerPosX, playerPosY + 1));
}

std::vector<sf::Sprite> GameBoard::setUpSprites() {

	std::vector<sf::Sprite> spriteVec;

	for (uint16_t i = 0; i < 15; i++) {
		for (uint16_t j = 0; j < 15; j++) {
			sf::Sprite tempSprite = boardVec.at(i * 15 + j)->createSprite();

			if (boardVec.at(i * 15 + j)->getType() == "bullet" || boardVec.at(i * 15 + j)->getType() == "enemy")
			{
				tempSprite.setPosition(TILE_SIZE * j + TILE_SIZE * 0.5, TILE_SIZE * i + TILE_SIZE * 0.5);
			}
			else

				// in cazul in care este tank, avem nevoie sa rotim sprite-ul, 
				// inainte de rotatie, ca tank-ul sa nu isi modifice pozitia, origin-ul este setat in mijlocul sprite-ului, 
				// nu in coltul din stanga sus cum este by default in SFML,
				// deci vom pozitiona sprite-ul corect
				if (boardVec.at(i * 15 + j)->getType() == "tank") {

					if (((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->getIsMoving()) {

						char direction = ((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->getDirection();

						switch (direction) {

						case DIR_UP:

							//TODO: handle smooth movement

							((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsMoving(false);
							break;

						case DIR_DOWN:

							//TODO: handle smooth movement

							((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsMoving(false);
							break;

						case DIR_LEFT:

							//TODO: handle smooth movement

							((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsMoving(false);
							break;

						case DIR_RIGHT:

							//TODO: handle smooth movement

							((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsMoving(false);
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

	return spriteVec;
}

void GameBoard::draw() {

	createLevel();
	
	Menu menu;
	int savedMenuOption = menu.getMenuOption();
	sf::Sprite menuSprite = menu.createSprite();

	sf::Font menuFont = menu.getMenuFont();
	sf::Text startText("Start", menuFont);
	sf::Text exitText("Exit", menuFont);
	sf::Text pauseText("Pause", menuFont);

	startText.setPosition(200, 310);
	exitText.setPosition(215, 380);

	startText.setFillColor(menu.getMenuOption() ? sf::Color::White : sf::Color::Yellow);
	exitText.setFillColor(menu.getMenuOption() ? sf::Color::Yellow : sf::Color::White);

	sf::RenderWindow window(sf::VideoMode(530, 530), "Bootleg Battle City");
	window.setFramerateLimit(60);
	
	boardVec.at(playerPosX * 15 + playerPosY) = std::make_unique<Tank>(); //deseneaza playerul in punctul initial

	while (window.isOpen())
	{
		dt = deltaClock.restart();

		sf::Event event;		
		std::vector<sf::Sprite> spriteVec = setUpSprites();

		enemyLogic();

		while (window.pollEvent(event))
		{
			if (menu.getIsInMenu())

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
								savedMenuOption--;
								savedMenuOption = std::clamp(savedMenuOption, 0, 1);

								menu.setMenuOption(savedMenuOption);
								std::cout << menu.getMenuOption();
								break;

							case sf::Keyboard::Down:

								savedMenuOption = menu.getMenuOption();
								savedMenuOption++;
								savedMenuOption = std::clamp(savedMenuOption, 0, 1);

								menu.setMenuOption(savedMenuOption);
								std::cout << menu.getMenuOption();
								break;

							case sf::Keyboard::Enter: !menu.getMenuOption() ? menu.setIsInMenu(false) : window.close(); break;
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

							case sf::Keyboard::Up: executeOnKeyUp(); break;
							case sf::Keyboard::Down: executeOnKeyDown(); break;
							case sf::Keyboard::Left: executeOnKeyLeft(); break;
							case sf::Keyboard::Right: executeOnKeyRight(); break;
							case sf::Keyboard::Escape: window.close(); break;				
							case sf::Keyboard::P: menu.setIsInMenu(true); break;
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
			window.draw(startText);
			window.draw(exitText);
		}
		else

		for (auto const& sprite : spriteVec) {
			window.draw(sprite);
		}

		window.display();
		//std::this_thread::sleep_for(std::chrono::milliseconds(1)); //TODO: de vazut daca exista vreo diferenta signifiant vizibila dpdv vizual, gpu usage mi-a scazut de la 50% la 7%
	}

}