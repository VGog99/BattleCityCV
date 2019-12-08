#include "Enemy.h"
#include <iostream>

Enemy::Enemy()
{
	enemyTexture.loadFromFile("../resources/enemy.png");
	enemyHiddenTexture.loadFromFile("../resources/enemyHidden.png");
	enemyOnIceTexture.loadFromFile("../resources/enemyOnIce.png");
}

Enemy::Enemy(double posX, double posY, uint16_t speed, uint16_t damage, uint16_t direction)
	:Tank(posX, posY, speed, damage, direction)
{
}

char Enemy::randomMovement()
{
	return (char)(std::rand() % 4 + 48);
}

sf::Sprite Enemy::createSprite()
{
	sf::Sprite sprite;

	if (getIsHidden())
		sprite.setTexture(enemyHiddenTexture);
	else
		if (getIsOnIce())
			sprite.setTexture(enemyOnIceTexture);
		else
			sprite.setTexture(enemyTexture);

	sprite.setOrigin(sf::Vector2f(35 * 0.5, 35 * 0.5));

	switch (m_direction) {

	case DIR_UP:
		sprite.rotate(0.f);
		break;

	case DIR_RIGHT:
		sprite.rotate(90.f);
		break;

	case DIR_LEFT:
		sprite.rotate(-90.f);
		break;

	case DIR_DOWN:
		sprite.rotate(180.f);
		break;
	}
	return sprite;
}

std::string Enemy::getType() const{
	return "enemy";
}