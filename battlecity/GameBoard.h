#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "SDK.h"
#include <chrono>
#include <thread>

class GameBoard {

private:
	std::vector<std::unique_ptr<Tile>> boardVec;

public:
	GameBoard() {};
	~GameBoard() {};

	void createLevel();
	void draw();
};