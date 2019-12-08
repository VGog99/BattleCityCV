#include "Bullet.h"

Bullet::Bullet()
{
	setCanAdvance(false);
	setCanHideTank(false);
	setCanShootThrough(false);
	setHP(1);
	bulletTexture.loadFromFile("../resources/bullet.png");
	bulletOnWaterTexture.loadFromFile("../resources/bulletOnWater.png");
	bulletOnIceTexture.loadFromFile("../resources/bulletOnIce.png");
}

Bullet::~Bullet()
{
}

void Bullet::setDirection(const char direction)
{
	m_direction = direction;
}

char Bullet::getDirection() const
{
	return m_direction;
}

sf::Sprite Bullet::createSprite()
{
	sf::Sprite sprite;

	if (getIsOnWater())
		sprite.setTexture(bulletOnWaterTexture);
	else
		if (getIsOnIce())
			sprite.setTexture(bulletOnIceTexture);
		else
			sprite.setTexture(bulletTexture);
	
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

std::string Bullet::getType() const
{
	return "bullet";
}

void Bullet::setIsOnWater(bool isOnWater)
{
	m_isOnWater = isOnWater;
}
bool Bullet::getIsOnWater() const
{
	return m_isOnWater;
}
void Bullet::setIsOnIce(bool isOnIce)
{
	m_isOnIce = isOnIce;
}

bool Bullet::getIsOnIce() const
{
	return m_isOnIce;
}
