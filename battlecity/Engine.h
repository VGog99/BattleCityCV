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
#include "Animation.h"

class Engine {

private:
	bool m_gameStarted;
	bool m_gameOver;
	unsigned int m_stageChosen;
	unsigned int m_localPlayerKills;
	bool m_localPlayerTankIsMoving;
	Tank* m_localPlayerTank;
	std::vector<WorldEntity*> m_worldEntities;
	std::vector<Enemy*> m_enemyTanks;
	std::vector<std::unique_ptr<Bullet>> m_bulletVec;

	//std::vector<Bullet*> m_bullet;

public:
	
	Engine();
	~Engine();
	void runGame();
	bool moveTank(Tank* tankToMove, const char direction, float speed);
	bool tankAlreadyFired(Tank* tankToCheck);
	bool handleCollision(Tank* tankToCheck, sf::FloatRect& intersection);
	void setUpWorld(unsigned short stage);
	void doLocalPlayerMovement();
};

extern Engine gameEngine;