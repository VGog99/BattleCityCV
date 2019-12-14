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

sf::Texture Tank::getTexture() 
{
	return m_tankTexture;
}

Position Tank::getPosition() const
{
	return m_tankPosition;
}

Position Tank::getLastNonCollidedPosition() const
{
	return m_tankLastNonCollidedPosition;
}

void Tank::setLastNonCollidedPosition(const Position lastNonCollidedPosition)
{
	m_tankLastNonCollidedPosition = lastNonCollidedPosition;
}



