#include "Enemy.h"
#include <iostream>

Enemy::Enemy()
{
	enemyTexture.loadFromFile("../resources/enemy.png");
}

Enemy::Enemy(double posX, double posY, uint16_t speed, uint16_t damage, uint16_t direction)
	:Tank(posX, posY, speed, damage, direction)
{
}

char Enemy::randomMovement()
{
	std::cout << (char)(std::rand() % 4 + 48);
	return (char)(std::rand() % 4 + 48);
}


sf::Sprite Enemy::createSprite()
{
	sf::Sprite sprite(enemyTexture);
	sprite.setOrigin(sf::Vector2f(TILE_SIZE * 0.5, TILE_SIZE * 0.5));

	switch (getDirection()) {

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