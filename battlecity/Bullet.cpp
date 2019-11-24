#include "Bullet.h"

Bullet::Bullet()
{
	bulletTexture.loadFromFile("../resources/bullet.png");
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
	sf::Sprite sprite(bulletTexture);

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
