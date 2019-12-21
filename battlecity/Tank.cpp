#include "Tank.h"

Tank::Tank()
{
}

Tank::~Tank()
{
}

Tank::Tank(float posX, float posY) : m_tankPosition(std::make_pair(posX, posY))
{
	m_tankTexture.loadFromFile("../resources/tank.png");
	m_tankSprite.setTexture(m_tankTexture);
	m_tankTexture.setSmooth(true);
	m_tankSprite.setOrigin(sf::Vector2f(m_tankTexture.getSize().x * 0.5, m_tankTexture.getSize().y * 0.5));
	m_tankSprite.setPosition(m_tankPosition.first, m_tankPosition.second);
}

Position Tank::getPosition() const
{
	return m_tankPosition;
}

char Tank::getTankDirection()
{
	return m_tankDirection;
}

void Tank::setTankDirection(char direction)
{
	m_tankDirection = direction;
}


float Tank::getTankSpeed()
{
	return m_tankSpeed;
}

void Tank::setTankSpeed(float speed)
{
	m_tankSpeed = speed;
}



