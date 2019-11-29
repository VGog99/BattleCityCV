#pragma once
#include <stdlib.h>
#include "SDK.h"

class Enemy : public Tank
{
private:

	sf::Texture enemyTexture;

public:

	Enemy(); 
	Enemy(double posX, double posY, uint16_t speed, uint16_t damage, uint16_t direction); 
	void randomMovement(uint16_t posX, uint16_t posY);
	sf::Sprite createSprite();
	//void drawEnemy();
	std::string getType() const;

};

