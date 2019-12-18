#pragma once

#include <SFML\Graphics.hpp>
#include "Tank.h"
#include <iostream>
#include <vector>
#include "WorldEntity.h"
#include "Enemy.h"
#include "Menu.h"
#include "../Logging/Logger.h"
#include "Bullet.h"

class Engine {

private:
	bool m_gameStarted;
	bool m_gameOver;
	unsigned int m_localPlayerKills;
	
	Tank* m_localPlayerTank = new Tank(265.f, 650.f);

	std::vector<WorldEntity*> m_worldEntities;
	std::vector<Enemy*> m_enemyTanks;

	Bullet* m_bullet = new Bullet(265.f, 650.f);
	//std::vector<Bullet*> m_bullet;

public:
	
	Engine();
	~Engine();
	void runGame();
	bool moveTank(Tank* tankToMove, const char direction, float speed);
	bool bulletLogic(Bullet* bullet, Tank* tankToShoot, const char direction);
	bool handleCollision(Tank* tankToCheck);
	void setUpWorld();
	void doLocalPlayerMovement();
};

extern Engine gameEngine;