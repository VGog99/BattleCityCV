#include "Tank.h"

Tank::Tank()
{
	tankTexture.loadFromFile("../resources/tank.png");
}

Tank::Tank(double posX, double posY, uint16_t speed, uint16_t damage, char direction): m_position(posX,posY),m_speed(speed),m_damage(damage),m_direction(direction)
{
}

void Tank::setSpeed(uint16_t speed)
{
	m_speed = speed;
}

uint16_t Tank::getSpeed() const
{
	return m_speed;
}

sf::Sprite Tank::createSprite()
{
	sf::Sprite sprite(tankTexture);
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

void Tank::setDirection(const char direction) {
	m_direction = direction;
}


std::string Tank::getType() const {
	return "tank";
}