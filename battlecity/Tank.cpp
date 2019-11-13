#include "Tank.h"

Tank::Tank()
{

	tankTexture.loadFromFile("../resources/playerOne.gif");
}

Tank::Tank(double posX, double posY, int speed, int damage, int direction) 
{
	this->m_speed = speed;
	this->m_damage = damage;
	this->direction = direction;
}
void Tank::setSpeed(unsigned int speed)
{
	m_speed = speed;
}
unsigned int Tank::getSpeed()
{
	return m_speed;
}

sf::Sprite Tank::createSprite()
{
	sf::Sprite sprite(tankTexture);
	return sprite;
}