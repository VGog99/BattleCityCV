#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

Bullet::Bullet(float posX, float posY): m_bulletPosition(std::make_pair(posX, posY))
{
	m_bulletTexture.loadFromFile("../resources/bullet.png");
	m_bulletSprite.setTexture(m_bulletTexture);
	m_bulletTexture.setSmooth(true);
	m_bulletSprite.setOrigin(sf::Vector2f(m_bulletTexture.getSize().x * 0.5, m_bulletTexture.getSize().y * 0.5));
	m_bulletSprite.setPosition(m_bulletPosition.first, m_bulletPosition.second);
}

sf::Texture Bullet::getTexture()
{
	return m_bulletTexture;
}

Position Bullet::getPosition() const
{
	return m_bulletPosition;
}

Position Bullet::getLastNonCollidedPosition() const
{
	return m_bulletLastNonCollidedPosition;
}

void Bullet::setLastNonCollidedPosition(const Position lastNonCollidedPosition)
{
	m_bulletLastNonCollidedPosition = lastNonCollidedPosition;
}