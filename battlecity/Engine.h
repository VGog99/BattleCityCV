#pragma once

#include <SFML\Graphics.hpp>
#include "Tank.h"
#include <iostream>
#include <vector>
#include "WorldEntity.h"
#include "Enemy.h"
#include "Menu.h"
#include "../Logging/Logger.h"

class Engine {

private:
	bool m_gameStarted;
	bool m_gameOver;
	unsigned int m_localPlayerKills;

	
	Tank* m_localPlayerTank = new Tank(265.f, 650.f);

	std::vector<WorldEntity*> m_worldEntities;
	std::vector<Enemy*> m_enemyTanks;

public:
	
	Engine();
	~Engine();
	void runGame();
	bool moveTank(Tank* tankToMove, const char direction);
	bool handleCollision(Tank* tankToCheck);
	void setUpWorld();
};

extern Engine gameEngine;