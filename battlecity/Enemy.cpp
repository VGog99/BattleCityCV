#include "Enemy.h"

Enemy::Enemy()
{
	enemyTexture.loadFromFile("../resources/enemy.png");
}

Enemy::Enemy(double posX, double posY, uint16_t speed, uint16_t damage, uint16_t direction)
	:Tank(posX, posY, speed, damage, direction)
{
}

void Enemy::randomMovement(uint16_t posX, uint16_t posY)
{
	int rand = std::rand() % 4;
	if (rand == 0)
	{
		++posY;
	}
	else if (rand == 1)
	{
		++posX;
	}
	else if (rand == 2)
	{
		--posY;
	}
	else 
	{
		--posX;
	}
}

sf::Sprite Enemy::createSprite()
{
	sf::Sprite sprite(enemyTexture);
	return sprite;
}

std::string Enemy::getType() const{
	return "enemy";
}