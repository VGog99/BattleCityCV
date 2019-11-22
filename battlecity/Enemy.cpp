#include "Enemy.h"

Enemy::Enemy()
{
	enemyTexture.loadFromFile("../resources/enemy.png");
}

Enemy::Enemy(double posX, double posY, uint16_t speed, uint16_t damage, uint16_t direction)
	:Tank(posX, posY, speed, damage, direction)
{
}

sf::Sprite Enemy::createSprite()
{
	sf::Sprite sprite(enemyTexture);
	return sprite;
}

std::string Enemy::getType() const{
	return "enemy";
}