#pragma once

#include <SFML\Graphics.hpp>
#include "Tank.h"
#include <iostream>
#include <vector>
#include "WorldEntity.h"

class Engine {

private:
	bool m_gameStarted;
	bool m_gameOver;
	unsigned int m_localPlayerKills;

	sf::Sprite m_localPlayerSprite;
	Tank* m_localPlayerTank = new Tank(265.f, 650.f);

	std::vector<WorldEntity*> m_worldEntities;

public:
	
	Engine();
	~Engine();
	void runGame();
	void moveSprite(sf::Sprite& spriteToMove, const char direction);
	bool handleCollision(sf::Sprite& firstSprite);
	void setUpTextures();
};