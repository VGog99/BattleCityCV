#pragma once

#include "Tank.h"

class Enemy : public Tank
{
private:

	sf::Texture enemyTexture;

public:

	Enemy(); 
	Enemy(double posX, double posY, int speed, int damage, int direction); 
	sf::Sprite createSprite();
	void drawEnemy();
};

