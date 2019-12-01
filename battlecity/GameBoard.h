#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "SDK.h"
#include <chrono>
#include <thread>

class GameBoard {

private:
	std::vector<std::unique_ptr<Object>> boardVec;
	sf::Clock deltaClock;
	sf::Time dt;
	sf::Time lastMoveTime = sf::seconds(0.f);

	// initializam si salvam pozitia player-ului pentru a evita cautari inutile in vector sa gasim tank-ul
	uint16_t playerPosX = 13;
	uint16_t playerPosY = 5;

	// initializam si salvam pozitia enemy-ului
	uint16_t enemyPosX = 13;
	uint16_t enemyPosY = 9;

	std::string tileUnderTank = "road";

	uint16_t stageChosen = 0;

public:
	GameBoard() {};
	~GameBoard() {};

	void createLevel();
	void playerLogic();
	void enemyLogic();
	void executeOnKeyUp();
	void executeOnKeyDown();
	void executeOnKeyLeft();
	void executeOnKeyRight();
	void setStage(const uint16_t stage);
	uint16_t getStage() const;
	std::vector<sf::Sprite> setUpSprites();
	

	void draw();
};