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
#include "Macros.h"

class Engine {

private:
	bool m_gameStarted;
	bool m_gameOver;
	unsigned int m_currentStage = 0;
	unsigned int m_stageChosen;
	unsigned int m_localPlayerKills;
	bool m_localPlayerTankIsMoving;
	std::unique_ptr<Tank> m_localPlayerTank;
	std::vector<std::unique_ptr<WorldEntity>> m_worldEntities;
	std::vector<std::unique_ptr<WorldEntity>> m_iceVec;
	std::vector<std::unique_ptr<WorldEntity>> m_bushVec;
	std::vector<std::unique_ptr<Enemy>> m_enemyTanks;
	std::vector<std::unique_ptr<Bullet>> m_bulletVec;
	std::vector<Position> m_enemySpawnPoints;

	sf::SoundBuffer tankMovingBuffer;
	sf::Sound tankMoving;
	sf::SoundBuffer bulletBuffer;
	sf::SoundBuffer tankIdleBuffer;
	sf::SoundBuffer gameOverBuffer;
	sf::Sound bulletSound;
	sf::Sound gameOver;
	sf::Sound tankIdle;

	bool m_playedMusic;
	bool m_nextStageScene = true;

	sf::Texture m_enemyLifeTexture;
	std::vector<sf::Sprite> enemyLifeSprites;

public:
	
	Engine();
	~Engine();
	void runGame();
	bool moveTank(Tank* tankToMove, const char direction, float speed);
	bool tankAlreadyFired(Tank* tankToCheck);
	bool handleCollision(Tank* tankToCheck, sf::FloatRect& intersection);
	void setUpWorld(unsigned short stage);
	void doLocalPlayerMovement();
	void setlocalPlayerKills(const unsigned int localPlayerKills);
	unsigned int getLocalPlayerKills() const;
	void onStageStartPresets();
	void setGameOver(bool gameOver);
	void advanceStageSetup();
	void resetGameLogic();
};

extern Engine gameEngine;