#include "Enemy.h"

Enemy::Enemy()
{
	enemyTexture.loadFromFile("../resources/enemy.png");
}

Enemy::Enemy(double posX, double posY, int speed, int damage, int direction)
	:Tank(posX, posY, speed, damage, direction)
{
}

sf::Sprite Enemy::createSprite()
{
	sf::Sprite sprite(enemyTexture);
	return sprite;
}

std::string Enemy::getType() {
	return "enemy";
}