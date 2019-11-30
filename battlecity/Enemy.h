#pragma once
#include <stdlib.h>
#include "SDK.h"

class Enemy : public Tank
{
private:

	sf::Texture enemyTexture;
	//char m_enemyDirection;

public:

	Enemy(); 
	Enemy(double posX, double posY, uint16_t speed, uint16_t damage, uint16_t direction); 
	static char randomMovement();
	sf::Sprite createSprite();
	//void drawEnemy();

	//void setDirection(const char enemyDirection);
	//char getDirection() const;
	std::string getType() const;

};

