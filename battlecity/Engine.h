#pragma once

#include <SFML\Graphics.hpp>
#include "Tank.h"
#include <iostream>
#include <vector>
#include <sstream>
#include "WorldEntity.h"
#include "Enemy.h"
#include "Menu.h"
#include "../Logging/Logger.h"
#include "Bullet.h"
#include "AnimatedSprite.hpp"
#include "Macros.h"
#include "PowerUps.h"

class Engine {

private:
	bool m_gameStarted;
	bool m_gameOver;
	unsigned int m_currentStage = 0;
	unsigned int m_stageChosen;
	unsigned int m_localPlayerKills;
	unsigned int m_localPlayerScore = 0;
	unsigned short m_enemiesRespawned = 0;
	unsigned short m_starsCollected = 0;
	float m_secondsElapsed;
	bool m_localPlayerTankIsMoving;
	std::vector<std::unique_ptr<WorldEntity>> m_worldEntities;
	std::vector<std::unique_ptr<WorldEntity>> m_iceVec;
	std::vector<std::unique_ptr<WorldEntity>> m_bushVec;
	std::vector<std::unique_ptr<Enemy>> m_enemyTanks;
	std::vector<std::unique_ptr<Bullet>> m_bulletVec;
	std::vector<Position> m_enemySpawnPoints;
	std::vector<Position> m_powerUpSpawnPoints;
	std::vector<PowerUps> m_powerUps;

	sf::SoundBuffer tankMovingBuffer;
	sf::SoundBuffer bulletBuffer;
	sf::SoundBuffer tankIdleBuffer;
	sf::SoundBuffer gameOverBuffer;
	sf::SoundBuffer wallHitSoundBuffer;
	sf::SoundBuffer tankHitSoundBuffer;
	sf::SoundBuffer solidHitSoundBuffer;
	sf::Sound solidHitSound;
	sf::Sound tankHitSound;
	sf::Sound tankMoving;
	sf::Sound bulletSound;
	sf::Sound gameOver;
	sf::Sound tankIdle;
	sf::Sound wallHitSound;

	bool m_playedMusic;
	bool m_nextStageScene = true;
	bool m_wallHit = false;
	bool m_tankHit = false;
	bool m_solidHit = false;

	sf::Texture m_enemyLifeTexture;
	sf::Texture m_explosionTextureSheet;
	sf::Texture m_spawnAnimTextureSheet;
	std::vector<sf::Sprite> enemyLifeSprites;
	std::vector<AnimatedSprite> spawnAnimVec;

public:
	
	std::unique_ptr<Tank> m_localPlayerTank;
	Animation explosionAnim;
	Animation spawnAnim;
	std::vector<AnimatedSprite> explosionsVec;
	Position m_localPlayerSpawnPoint;
	AnimatedSprite* m_localPlayerSpawnSprite;
	std::vector<bool> m_activePowerUps = { false, false, false, false, false, false};

	unsigned short m_localPlayerLives[2] = { 2, 2 };

	Engine();
	~Engine();
	void runGame();
	bool moveTank(Tank* tankToMove, const char direction, float speed);
	unsigned short tankAlreadyFired(Tank* tankToCheck);
	bool handleCollision(Tank* tankToCheck, char direction);
	void setUpWorld(unsigned short stage);
	void doLocalPlayerMovement();
	void setlocalPlayerKills(const unsigned int localPlayerKills);
	unsigned int getLocalPlayerKills() const;
	void setLocalPlayerScore(const uint64_t localPlayerScore);
	uint64_t getLocalPlayerScore() const;
	void onStageStartPresets();
	void setGameOver(bool gameOver);
	void advanceStageSetup();
	void resetGameLogic();
	void setUpPUSpawnPoints();
	unsigned short getStarsCollected() const;
	void setStarsCollected(unsigned short stars);
	Animation createExplosionAnimation();
	Animation createSpawnAnimation();
};

extern Engine gameEngine;