#include "GameBoard.h"
#include <iostream>
#include <fstream>
#include <string>

void GameBoard::createLevel() {

	int inputFromFile;

	std::string filePath;
	switch (stageChosen)
	{
	case 0:
		filePath = "../stages/stage1.txt";
		break;
	case 1:
		filePath = "../stages/stage2.txt";
		break;
	case 2:
		filePath = "../stages/stage3.txt";
		break;
	case 3:
		filePath = "../stages/stage4.txt";
		break;
	}
	std::ifstream file(filePath);

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

			case 6:

				boardVec.at(i * MATRIX_SIZE + j) = std::make_unique<Bush>();
				break;

			case 7:

				boardVec.at(i * MATRIX_SIZE + j) = std::make_unique<Water>();
				break;

			case 8:

				boardVec.at(i * MATRIX_SIZE + j) = std::make_unique<Ice>();
				break;

			case 11:		//locatie sapwn 1

				boardVec.at(i * MATRIX_SIZE + j) = std::make_unique<Enemy>();
				enemyPosX = i;
				enemyPosY = j;
				break;

			case 12:		//locatie spawn 2

				boardVec.at(i * MATRIX_SIZE + j) = std::make_unique<Enemy>();
				enemyPosX = i;
				enemyPosY = j;
				break;

			case 13:		//locatie spawn 3

				boardVec.at(i * MATRIX_SIZE + j) = std::make_unique<Enemy>();
				enemyPosX = i;
				enemyPosY = j;
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
				if (tileUnderEnemy == "road")
				{
					std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY));
					enemyPosX--;
					tileUnderEnemy = "road";
				}
				else
					if (tileUnderEnemy == "bush")
					{
						std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY));
						enemyPosX--;
						boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY) = std::make_unique<Bush>();
						tileUnderEnemy = "road";
						((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsHidden(false);
					}
					else
						if (tileUnderEnemy == "ice")
						{
							std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY));
							enemyPosX--;
							boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY) = std::make_unique<Ice>();
							tileUnderEnemy = "road";
							((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsOnIce(false);
						}
			}
			else
				if (boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY)->getType() == "bush")
			{
					if (tileUnderEnemy == "road")
					{
						std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY));
						enemyPosX--;
						boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY) = std::make_unique<Road>();
						tileUnderEnemy = "bush";
						((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsHidden(true);

					}
					else
						if (tileUnderEnemy == "bush")
						{
							std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY));
							enemyPosX--;
							boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY) = std::make_unique<Bush>();
							tileUnderEnemy = "bush";
						}
						else
							if (tileUnderEnemy == "ice")
							{
								std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY));
								enemyPosX--;
								boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY) = std::make_unique<Ice>();
								tileUnderEnemy = "bush";
								((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsOnIce(false);
								((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsHidden(true);
							}
			}
				else
					if (boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY)->getType() == "ice")
					{
						if (tileUnderEnemy == "road")
						{
							std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY));
							enemyPosX--;
							boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY) = std::make_unique<Road>();
							tileUnderEnemy = "ice";
							((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsOnIce(true);

						}
						else
							if (tileUnderEnemy == "bush")
							{
								std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY));
								enemyPosX--;
								boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY) = std::make_unique<Bush>();
								tileUnderEnemy = "ice";
								((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsOnIce(true);
								((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsHidden(false);
							}
							else
								if (tileUnderEnemy == "ice" && boardVec.at((enemyPosX - 2) * MATRIX_SIZE + enemyPosY)->getType() == "ice")
								{
									std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX - 2) * MATRIX_SIZE + enemyPosY));
									enemyPosX = enemyPosX - 2;
									boardVec.at((enemyPosX + 2) * MATRIX_SIZE + enemyPosY) = std::make_unique<Ice>();
									tileUnderEnemy = "ice";
								}
								else
								{
									std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY));
									enemyPosX--;
									boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY) = std::make_unique<Ice>();
									tileUnderEnemy = "ice";
								}
					}
			break;

		case DIR_DOWN:

			((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setDirection(DIR_DOWN);

			if (boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY)->getType() == "road")
			{
				if (tileUnderEnemy == "road")
				{
					std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY));
					enemyPosX++;
					tileUnderEnemy = "road";
				}
				else
					if (tileUnderEnemy == "bush")
					{
						std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY));
						enemyPosX++;
						boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY) = std::make_unique<Bush>();
						tileUnderEnemy = "road";
						((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsHidden(false);
					}
					else
						if (tileUnderEnemy == "ice")
						{
							std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY));
							enemyPosX++;
							boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY) = std::make_unique<Ice>();
							tileUnderEnemy = "road";
							((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsOnIce(false);
						}
			}
			else
				if (boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY)->getType() == "bush")
				{
					if (tileUnderEnemy == "road")
					{
						std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY));
						enemyPosX++;
						boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY) = std::make_unique<Road>();
						tileUnderEnemy = "bush";
						((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsHidden(true);

					}
					else
						if (tileUnderEnemy == "bush")
						{
							std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY));
							enemyPosX++;
							boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY) = std::make_unique<Bush>();
							tileUnderEnemy = "bush";
						}
						else
							if (tileUnderEnemy == "ice")
							{
								std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY));
								enemyPosX++;
								boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY) = std::make_unique<Ice>();
								tileUnderEnemy = "bush";
								((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsOnIce(false);
								((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsHidden(true);
							}
				}
				else
					if (boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY)->getType() == "ice")
					{
						if (tileUnderEnemy == "road")
						{
							std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY));
							enemyPosX++;
							boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY) = std::make_unique<Road>();
							tileUnderEnemy = "ice";
							((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsOnIce(true);

						}
						else
							if (tileUnderEnemy == "bush")
							{
								std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY));
								enemyPosX++;
								boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY) = std::make_unique<Bush>();
								tileUnderEnemy = "ice";
								((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsOnIce(true);
								((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsHidden(false);
							}
							else
								if (tileUnderEnemy == "ice" && boardVec.at((enemyPosX + 2) * MATRIX_SIZE + enemyPosY)->getType() == "ice")
								{
									std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX + 2) * MATRIX_SIZE + enemyPosY));
									enemyPosX = enemyPosX + 2;
									boardVec.at((enemyPosX - 2) * MATRIX_SIZE + enemyPosY) = std::make_unique<Ice>();
									tileUnderEnemy = "ice";
								}
								else
								{
									std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at((enemyPosX + 1) * MATRIX_SIZE + enemyPosY));
									enemyPosX++;
									boardVec.at((enemyPosX - 1) * MATRIX_SIZE + enemyPosY) = std::make_unique<Ice>();
									tileUnderEnemy = "ice";
								}
					}

			break;

		case DIR_LEFT:

			((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setDirection(DIR_LEFT);

			if (boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1))->getType() == "road")
			{
				if (tileUnderEnemy == "road")
				{
					std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1)));
					enemyPosY--;
					tileUnderEnemy = "road";
				}
				else
					if (tileUnderEnemy == "bush")
					{
						std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1)));
						enemyPosY--;
						boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1)) = std::make_unique<Bush>();
						tileUnderEnemy = "road";
						((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsHidden(false);
					}
					else
						if (tileUnderEnemy == "ice")
						{
							std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1)));
							enemyPosY--;
							boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1)) = std::make_unique<Ice>();
							tileUnderEnemy = "road";
							((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsOnIce(false);
						}
			}
			else
				if (boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1))->getType() == "bush")
				{
					if (tileUnderEnemy == "road")
					{
						std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1)));
						enemyPosY--;
						boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1)) = std::make_unique<Road>();
						tileUnderEnemy = "bush";
						((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsHidden(true);

					}
					else
						if (tileUnderEnemy == "bush")
						{
							std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1)));
							enemyPosY--;
							boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1)) = std::make_unique<Bush>();
							tileUnderEnemy = "bush";
						}
						else
							if (tileUnderEnemy == "ice")
							{
								std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1)));
								enemyPosY--;
								boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1)) = std::make_unique<Ice>();
								tileUnderEnemy = "bush";
								((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsOnIce(false);
								((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsHidden(true);
							}
				}
				else
					if (boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1))->getType() == "ice")
					{
						if (tileUnderEnemy == "road")
						{
							std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1)));
							enemyPosY--;
							boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1)) = std::make_unique<Road>();
							tileUnderEnemy = "ice";
							((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsOnIce(true);

						}
						else
							if (tileUnderEnemy == "bush")
							{
								std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1)));
								enemyPosY--;
								boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1)) = std::make_unique<Bush>();
								tileUnderEnemy = "ice";
								((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsOnIce(true);
								((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsHidden(false);
							}
							else
								if (tileUnderEnemy == "ice" && boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 2))->getType() == "ice")
								{
									std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 2)));
									enemyPosY = enemyPosY - 2;
									boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 2)) = std::make_unique<Ice>();
									tileUnderEnemy = "ice";
								}
								else
								{
									std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1)));
									enemyPosY--;
									boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1)) = std::make_unique<Ice>();
									tileUnderEnemy = "ice";
								}
					}

			break;

		case DIR_RIGHT:

			((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setDirection(DIR_RIGHT);

			if (boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1))->getType() == "road")
			{
				if (tileUnderEnemy == "road")
				{
					std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1)));
					enemyPosY++;
					tileUnderEnemy = "road";
				}
				else
					if (tileUnderEnemy == "bush")
					{
						std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1)));
						enemyPosY++;
						boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1)) = std::make_unique<Bush>();
						tileUnderEnemy = "road";
						((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsHidden(false);
					}
					else
						if (tileUnderEnemy == "ice")
						{
							std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1)));
							enemyPosY++;
							boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1)) = std::make_unique<Ice>();
							tileUnderEnemy = "road";
							((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsOnIce(false);
						}
			}
			else
				if (boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1))->getType() == "bush")
				{
					if (tileUnderEnemy == "road")
					{
						std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1)));
						enemyPosY++;
						boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1)) = std::make_unique<Road>();
						tileUnderEnemy = "bush";
						((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsHidden(true);

					}
					else
						if (tileUnderEnemy == "bush")
						{
							std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1)));
							enemyPosY++;
							boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1)) = std::make_unique<Bush>();
							tileUnderEnemy = "bush";
						}
						else
							if (tileUnderEnemy == "ice")
							{
								std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1)));
								enemyPosY++;
								boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1)) = std::make_unique<Ice>();
								tileUnderEnemy = "bush";
								((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsOnIce(false);
								((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsHidden(true);
							}
				}
				else
					if (boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1))->getType() == "ice")
					{
						if (tileUnderEnemy == "road")
						{
							std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1)));
							enemyPosY++;
							boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1)) = std::make_unique<Road>();
							tileUnderEnemy = "ice";
							((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsOnIce(true);

						}
						else
							if (tileUnderEnemy == "bush")
							{
								std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1)));
								enemyPosY++;
								boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1)) = std::make_unique<Bush>();
								tileUnderEnemy = "ice";
								((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsOnIce(true);
								((Enemy*)boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY).get())->setIsHidden(false);
							}
							else
						if (tileUnderEnemy == "ice" && boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 2))->getType() == "ice")
						{
							std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 2)));
							enemyPosY = enemyPosY + 2;
							boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 2)) = std::make_unique<Ice>();
							tileUnderEnemy = "ice";
						}
						else
								{
									std::swap(boardVec.at(enemyPosX * MATRIX_SIZE + enemyPosY), boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY + 1)));
									enemyPosY++;
									boardVec.at(enemyPosX * MATRIX_SIZE + (enemyPosY - 1)) = std::make_unique<Ice>();
									tileUnderEnemy = "ice";
								}
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
		else
		if (tileUnderTank == "bush")
		{
			std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX - 1) * 15 + playerPosY));
			playerPosX--;
			boardVec.at((playerPosX + 1) * 15 + playerPosY) = std::make_unique<Bush>();
			tileUnderTank = "road";
			((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsHidden(false);
		}
		else
		if (tileUnderTank == "ice")
		{
			std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX - 1) * 15 + playerPosY));
			playerPosX--;
			boardVec.at((playerPosX + 1) * 15 + playerPosY) = std::make_unique<Ice>();
			tileUnderTank = "road";
			((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsOnIce(false);
		}

	}
	else
		if (boardVec.at((playerPosX - 1) * 15 + playerPosY)->getType() == "bush")
		{
			if (tileUnderTank == "bush")
			{
				std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX - 1) * 15 + playerPosY));
				playerPosX--;
				boardVec.at((playerPosX + 1) * 15 + playerPosY) = std::make_unique<Bush>();
				tileUnderTank = "bush";
			}
			else
			if (tileUnderTank == "road") 
			{
				std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX - 1) * 15 + playerPosY));
				playerPosX--;
				boardVec.at((playerPosX + 1) * 15 + playerPosY) = std::make_unique<Road>();
				((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsHidden(true);
				tileUnderTank = "bush";
			}
			else
				if (tileUnderTank == "ice")
				{
					std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX - 1) * 15 + playerPosY));
					playerPosX--;
					boardVec.at((playerPosX + 1) * 15 + playerPosY) = std::make_unique<Ice>();
					((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsHidden(true);
					((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsOnIce(false);
					tileUnderTank = "bush";
				}

		}
		else
			if (boardVec.at((playerPosX - 1) * 15 + playerPosY)->getType() == "ice")
			{
				if (tileUnderTank == "ice" && boardVec.at((playerPosX - 2) * 15 + playerPosY)->getType() == "ice")
				{
					std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX - 2) * 15 + playerPosY));
					playerPosX = playerPosX - 2;
					boardVec.at((playerPosX + 2) * 15 + playerPosY) = std::make_unique<Ice>();
					tileUnderTank = "ice";
				}
				else
				if (tileUnderTank == "ice")
				{
					std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX - 1) * 15 + playerPosY));
					playerPosX--;
					boardVec.at((playerPosX + 1) * 15 + playerPosY) = std::make_unique<Ice>();
					tileUnderTank = "ice";
				}
				else
					if (tileUnderTank == "road")
					{
						std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX - 1) * 15 + playerPosY));
						playerPosX--;
						boardVec.at((playerPosX + 1) * 15 + playerPosY) = std::make_unique<Road>();
						((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsOnIce(true);
						tileUnderTank = "ice";
					}
					else
						if (tileUnderTank == "bush")
						{
							std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX - 1) * 15 + playerPosY));
							playerPosX--;
							boardVec.at((playerPosX + 1) * 15 + playerPosY) = std::make_unique<Bush>();
							((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsHidden(false);
							((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsOnIce(true);
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
		else
		if (tileUnderTank == "bush")
		{
			std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX + 1) * 15 + playerPosY));
			playerPosX++;
			boardVec.at((playerPosX - 1) * 15 + playerPosY) = std::make_unique<Bush>();
			tileUnderTank = "road";
			((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsHidden(false);
		}
		else 
			if (tileUnderTank == "ice")
			{
				std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX + 1) * 15 + playerPosY));
				playerPosX++;
				boardVec.at((playerPosX - 1) * 15 + playerPosY) = std::make_unique<Ice>();
				tileUnderTank = "road";
				((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsOnIce(false);
		    }

	}
	else
		if (boardVec.at((playerPosX + 1) * 15 + playerPosY)->getType() == "bush")
		{
			if (tileUnderTank == "bush")
			{
				std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX + 1) * 15 + playerPosY));
				playerPosX++;
				boardVec.at((playerPosX - 1) * 15 + playerPosY) = std::make_unique<Bush>();
				tileUnderTank = "bush";
			}
			else
				if (tileUnderTank == "road")
				{
					std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX + 1) * 15 + playerPosY));
					playerPosX++;
					boardVec.at((playerPosX - 1) * 15 + playerPosY) = std::make_unique<Road>();
					((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsHidden(true);
					tileUnderTank = "bush";
				}
				else
					if (tileUnderTank == "ice")
					{
						std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX + 1) * 15 + playerPosY));
						playerPosX++;
						boardVec.at((playerPosX - 1) * 15 + playerPosY) = std::make_unique<Ice>();
						tileUnderTank = "road";
						((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsOnIce(false);
						((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsHidden(true);
					}

		}
		else
			if (boardVec.at((playerPosX + 1) * 15 + playerPosY)->getType() == "ice")
			{
				if (tileUnderTank == "ice" && boardVec.at((playerPosX + 2) * 15 + playerPosY)->getType() == "ice")
				{
					std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX + 2) * 15 + playerPosY));
					playerPosX = playerPosX + 2;
					boardVec.at((playerPosX - 2) * 15 + playerPosY) = std::make_unique<Ice>();
					tileUnderTank = "ice";
				}
				else
				if (tileUnderTank == "ice")
				{
					std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX + 1) * 15 + playerPosY));
					playerPosX++;
					boardVec.at((playerPosX - 1) * 15 + playerPosY) = std::make_unique<Ice>();
					tileUnderTank = "ice";
				}
				else
					if (tileUnderTank == "road")
					{
						std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX + 1) * 15 + playerPosY));
						playerPosX++;
						boardVec.at((playerPosX - 1) * 15 + playerPosY) = std::make_unique<Road>();
						((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsOnIce(true);
						tileUnderTank = "ice";
					}
					else
						if (tileUnderTank == "bush")
						{
							std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at((playerPosX + 1) * 15 + playerPosY));
							playerPosX++;
							boardVec.at((playerPosX - 1) * 15 + playerPosY) = std::make_unique<Bush>();
							tileUnderTank = "ice";
							((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsOnIce(true);
							((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsHidden(false);
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
		else
		if (tileUnderTank == "bush")
		{
			std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY - 1)));
			playerPosY--;
			boardVec.at((playerPosX) * 15 + (playerPosY+1)) = std::make_unique<Bush>();
			tileUnderTank = "road";
			((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsHidden(false);
		}
		else
			if (tileUnderTank == "ice")
			{
				std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY - 1)));
				playerPosY--;
				boardVec.at((playerPosX) * 15 + (playerPosY + 1)) = std::make_unique<Ice>();
				tileUnderTank = "road";
				((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsOnIce(false);
			}

	}
	else
		if (boardVec.at(playerPosX * 15 + (playerPosY - 1))->getType() == "bush")
		{

			if (tileUnderTank == "bush")
			{
				std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY - 1)));
				playerPosY--;
				boardVec.at((playerPosX) * 15 + (playerPosY + 1)) = std::make_unique<Bush>();
				tileUnderTank = "bush";
			}
			else
				if (tileUnderTank == "road")
				{
					std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY - 1)));
					playerPosY--;
					boardVec.at((playerPosX) * 15 + (playerPosY+1)) = std::make_unique<Road>();
					((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsHidden(true);
					tileUnderTank = "bush";
				}
				else
					if (tileUnderTank == "ice")
					{
						std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY - 1)));
						playerPosY--;
						boardVec.at((playerPosX) * 15 + (playerPosY + 1)) = std::make_unique<Ice>();
						tileUnderTank = "bush";
						((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsOnIce(false);
						((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsHidden(true);
					}

		}
		else
			if (boardVec.at(playerPosX * 15 + (playerPosY - 1))->getType() == "ice")
			{
				if (tileUnderTank == "ice" && boardVec.at(playerPosX * 15 + (playerPosY - 2))->getType() == "ice")
				{
					std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY - 2)));
					playerPosY = playerPosY - 2;
					boardVec.at((playerPosX) * 15 + (playerPosY + 2)) = std::make_unique<Ice>();
					tileUnderTank = "ice";
				}
				else
				if (tileUnderTank == "ice")
				{
					std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY - 1)));
					playerPosY--;
					boardVec.at((playerPosX) * 15 + (playerPosY + 1)) = std::make_unique<Ice>();
					tileUnderTank = "ice";
				}
				else
					if (tileUnderTank == "road")
					{
						std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY - 1)));
						playerPosY--;
						boardVec.at((playerPosX) * 15 + (playerPosY + 1)) = std::make_unique<Road>();
						((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsOnIce(true);
						tileUnderTank = "ice";
					}
					else
						if (tileUnderTank == "bush")
						{
							std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY - 1)));
							playerPosY--;
							boardVec.at((playerPosX) * 15 + (playerPosY + 1)) = std::make_unique<Bush>();
							tileUnderTank = "ice";
							((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsOnIce(true);
							((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsHidden(false);
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
		else
		if (tileUnderTank == "bush")
		{
			std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY + 1)));
			playerPosY++;
			boardVec.at(playerPosX * 15 + (playerPosY - 1)) = std::make_unique<Bush>();
			tileUnderTank = "road";
			((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsHidden(false);
		}
		else
		if (tileUnderTank == "ice")
		{
			std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY + 1)));
			playerPosY++;
			boardVec.at(playerPosX * 15 + (playerPosY - 1)) = std::make_unique<Ice>();
			tileUnderTank = "road";
			((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsOnIce(false);
		}

	}
	else
		if (boardVec.at(playerPosX * 15 + (playerPosY + 1))->getType() == "bush")
		{
			if (tileUnderTank == "bush")
			{
				std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY + 1)));
				playerPosY++;
				boardVec.at(playerPosX * 15 + (playerPosY - 1)) = std::make_unique<Bush>();
				tileUnderTank = "bush";
			}
			else
				if (tileUnderTank == "road")
				{
					std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY + 1)));
					playerPosY++;
					boardVec.at(playerPosX * 15 + (playerPosY - 1)) = std::make_unique<Road>();
					((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsHidden(true);
					tileUnderTank = "bush";
				}
				else
					if (tileUnderTank == "ice")
					{
						std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY + 1)));
						playerPosY++;
						boardVec.at(playerPosX * 15 + (playerPosY - 1)) = std::make_unique<Ice>();
						tileUnderTank = "bush";
						((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsOnIce(false);
						((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsHidden(true);
					}
					

		}
		else
			if (boardVec.at(playerPosX * 15 + (playerPosY + 1))->getType() == "ice")
			{
				if (tileUnderTank == "ice" && boardVec.at(playerPosX * 15 + (playerPosY + 2))->getType() == "ice")
				{
					std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY + 2)));
					playerPosY = playerPosY + 2;
					boardVec.at((playerPosX) * 15 + (playerPosY - 2)) = std::make_unique<Ice>();
					tileUnderTank = "ice";
				}
				else
				if (tileUnderTank == "ice")
				{
					std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY + 1)));
					playerPosY++;
					boardVec.at(playerPosX * 15 + (playerPosY - 1)) = std::make_unique<Ice>();
					tileUnderTank = "ice";
				}
				else
				if (tileUnderTank == "road")
				{
					std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY + 1)));
					playerPosY++;
					boardVec.at(playerPosX * 15 + (playerPosY - 1)) = std::make_unique<Road>();
					((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsOnIce(true);
					tileUnderTank = "ice";
				}
				else
					if (tileUnderTank == "ice")
					{
						std::swap(boardVec.at(playerPosX * 15 + playerPosY), boardVec.at(playerPosX * 15 + (playerPosY + 1)));
						playerPosY++;
						boardVec.at(playerPosX * 15 + (playerPosY - 1)) = std::make_unique<Bush>();
						tileUnderTank = "ice";
						((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsOnIce(true);
						((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsHidden(false);
					}

			}

	if (((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->getIsMoving())
		return;

	((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setIsMoving(true);
	((Tank*)boardVec.at(playerPosX * 15 + playerPosY).get())->setFuturePosition(std::make_pair(playerPosX, playerPosY + 1));
}

void GameBoard::executeOnKeySpace()
{

		char direction = ((Tank*)boardVec.at(playerPosX * MATRIX_SIZE + playerPosY).get())->getDirection();
		lastMoveTime += dt;
		switch (direction) {
		
		case DIR_UP:

			bulletPosX = (playerPosX - 1);
			bulletPosY = playerPosY;
			
			while (boardVec.at((playerPosX - 1) * MATRIX_SIZE + playerPosY)->getCanShootThrough())
			{
				
					boardVec.at((playerPosX - 1) * MATRIX_SIZE + playerPosY) = std::make_unique<Bullet>();

					if (tileUnderBullet == "road")
					{
						std::swap(boardVec.at(bulletPosX * MATRIX_SIZE + bulletPosY), boardVec.at((bulletPosX - 1) * MATRIX_SIZE + bulletPosY));
						bulletPosX--;
						tileUnderBullet = "road";
					}
					else if (tileUnderBullet == "water")
					{
						std::swap(boardVec.at(bulletPosX * MATRIX_SIZE + bulletPosY), boardVec.at((bulletPosX - 1) * MATRIX_SIZE + bulletPosY));
						bulletPosX--;
						tileUnderBullet = "water";
					}
					else if (tileUnderBullet == "ice")
					{
						std::swap(boardVec.at(bulletPosX * MATRIX_SIZE + bulletPosY), boardVec.at((bulletPosX - 1) * MATRIX_SIZE + bulletPosY));
						bulletPosX--;
						tileUnderBullet = "ice";
					}
					else if (tileUnderBullet == "bush")
					{
						std::swap(boardVec.at(bulletPosX * MATRIX_SIZE + bulletPosY), boardVec.at((bulletPosX - 1) * MATRIX_SIZE + bulletPosY));
						bulletPosX--;
						tileUnderBullet = "bush";
					}

					
				
			}
			break;

		case  DIR_DOWN:

			if (boardVec.at((playerPosX + 1) * 15 + playerPosY)->getCanShootThrough())
				std::cout << "- shoot -";
			break;

		case DIR_LEFT:

			if (boardVec.at(playerPosX * 15 + (playerPosY - 1))->getCanShootThrough())
				std::cout << "- shoot -";
			break;

		case DIR_RIGHT:

			if (boardVec.at(playerPosX * 15 + (playerPosY + 1))->getCanShootThrough())
				std::cout << "- shoot -";
			break;
		}
		
	}

void GameBoard::bulletLogic()
{



}




void GameBoard::setStage(const uint16_t stage)
{
	stageChosen = stage;
}

uint16_t GameBoard::getStage() const
{
	return stageChosen;
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


	Menu menu;

	int savedMenuOption = menu.getMenuOption();
	sf::Sprite menuSprite = menu.createSprite();

	sf::Font menuFont = menu.getMenuFont();
	sf::Text startText("Start", menuFont);
	sf::Text exitText("Exit", menuFont);
	sf::Text pauseText("Pause", menuFont);
	sf::Text stageText("Choose your stage \n(use arrow keys)", menuFont);
	sf::Text stageOne("Stage 1", menuFont);
	sf::Text stageTwo("Stage 2", menuFont);
	sf::Text stageThree("Stage 3", menuFont);
	sf::Text stageFour("Stage 4", menuFont);

	sf::Music menuMusic;

	if (!menuMusic.openFromFile("../resources/menumusic.wav"))
	{
		std::cout << "Nu s-a putut incarca fisierul de muzica.";
	}

	menuMusic.setVolume(0.60f);
	menuMusic.play();

	startText.setPosition(200, 310);
	exitText.setPosition(215, 380);
	stageText.setCharacterSize(25.f);
	stageText.setPosition(50, 150);
	stageOne.setCharacterSize(20.f);
	stageOne.setPosition(200, 250);
	stageTwo.setCharacterSize(20.f);
	stageTwo.setPosition(200, 300);
	stageThree.setCharacterSize(20.f);
	stageThree.setPosition(200, 350);
	stageFour.setCharacterSize(20.f);
	stageFour.setPosition(200, 400);

	sf::RenderWindow window(sf::VideoMode(530, 530), "Bootleg Battle City");
	window.setFramerateLimit(60);
	
	if (!menu.getIsInMenu())
		boardVec.at(playerPosX * 15 + playerPosY) = std::make_unique<Tank>(); //deseneaza playerul in punctul initial

	while (window.isOpen())
	{
		dt = deltaClock.restart();

		sf::Event event;	

		std::vector<sf::Sprite> spriteVec;
		
		if (!menu.getIsInMenu())
			spriteVec = setUpSprites();

		if (menu.getIsInMenu()) {
			startText.setFillColor(menu.getMenuOption() ? sf::Color::White : sf::Color::Yellow);
			exitText.setFillColor(menu.getMenuOption() ? sf::Color::Yellow : sf::Color::White);
			stageOne.setFillColor(menu.getMenuOption() == 0 ? sf::Color::Yellow : sf::Color::White);
			stageTwo.setFillColor(menu.getMenuOption() == 1 ? sf::Color::Yellow : sf::Color::White);
			stageThree.setFillColor(menu.getMenuOption() == 2 ? sf::Color::Yellow : sf::Color::White);
			stageFour.setFillColor(menu.getMenuOption() == 3 ? sf::Color::Yellow : sf::Color::White);

		}

		if (!menu.getIsInMenu())
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
								savedMenuOption = std::clamp(savedMenuOption, 0, menu.getStageChooser() ? 3 : 1);

								menu.setMenuOption(savedMenuOption);
								std::cout << menu.getMenuOption();
								
								break;

							case sf::Keyboard::Down:

								savedMenuOption = menu.getMenuOption();
								savedMenuOption++;
								savedMenuOption = std::clamp(savedMenuOption,  0, menu.getStageChooser() ? 3 : 1);

								menu.setMenuOption(savedMenuOption);
								std::cout << menu.getMenuOption();
								break;

							case sf::Keyboard::Enter: {

								if (!menu.getStageChooser()) {
									!menu.getMenuOption() ? menu.setStageChooser(true) : window.close(); 
									break;
								}
								else {
									if (menu.getMenuOption() == 0)
									{
										setStage(0);
										createLevel();

										menu.setIsInMenu(false);
									}
									else if(menu.getMenuOption() == 1)
									{
										setStage(1);
										createLevel();

										menu.setIsInMenu(false);
									}
									else if(menu.getMenuOption() == 2)
									{
										setStage(2);
										createLevel();

										menu.setIsInMenu(false);
									}
									else
									{
										setStage(3);
										createLevel();

										menu.setIsInMenu(false);
									}
								}
							}
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
							case sf::Keyboard::Space: executeOnKeySpace(); break;
						}
					}
				}
		}

		window.clear();

		// ----------------- DRAWING --------------------

		// draw game
		if (menu.getIsInMenu())
		{
			if (!menu.getStageChooser()) {
				window.draw(menuSprite);
				window.draw(startText);
				window.draw(exitText);
			}
			else
			{
				window.draw(stageText);
				window.draw(stageOne);
				window.draw(stageTwo);
				window.draw(stageThree);
				window.draw(stageFour);
			}
			
		}
		else {		
			for (auto const& sprite : spriteVec) {
				window.draw(sprite);
			}
		}



		window.display();
		//std::this_thread::sleep_for(std::chrono::milliseconds(1)); //TODO: de vazut daca exista vreo diferenta signifiant vizibila dpdv vizual, gpu usage mi-a scazut de la 50% la 7%
	}

}