#include "Tank.h"

Tank::Tank()
{

	tankTexture.loadFromFile("../resources/playerOne.gif");
}

Tank::Tank(double posX, double posY, int speed, int damage, int direction) 
{
	this->speed = speed;
	this->damage = damage;
	this->direction = direction;
}

sf::Sprite Tank::createSprite()
{
	sf::Sprite sprite(tankTexture);
	return sprite;
}