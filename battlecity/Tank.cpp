#include "Tank.h"

Tank::Tank()
{
	setCanAdvance(false);
	setCanHideTank(false);
	setCanShootThrough(false);
	setHP(1);
	tankTexture.loadFromFile("../resources/tank.png");
	tankHiddenTexture.loadFromFile("../resources/tankHidden.png");
	tankOnIceTexture.loadFromFile("../resources/tankOnIce.png");
	m_futurePosition.first = 13;
	m_futurePosition.second = 5;
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
	sf::Sprite sprite;
	if(getIsHidden())
		sprite.setTexture(tankHiddenTexture);
	else
		if(getIsOnIce())
			sprite.setTexture(tankOnIceTexture);
		else 
			sprite.setTexture(tankTexture);

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

bool Tank::getIsMoving() const {
	return m_isMoving;
}

std::pair<uint16_t, uint16_t> Tank::getFuturePosition() const {
	return m_futurePosition;
}

void Tank::setFuturePosition(std::pair<uint16_t, uint16_t> futurePosition) {
	m_futurePosition = futurePosition;
}

void Tank::setIsMoving(const bool isMoving) {
	m_isMoving = isMoving;
}

position Tank::getPosition() const {
	return m_position;
}

void Tank::setPosition(const position position) {
	m_position = position;
}

char Tank::getDirection() const {
	return m_direction;
}

std::string Tank::getType() const {
	return "tank";
}
void Tank::setIsHidden(bool isHidden)
{
	m_isHidden = isHidden;
}
bool Tank::getIsHidden() const
{
	return m_isHidden;
}
void Tank::setIsOnIce(bool isOnIce)
{
	m_isOnIce = isOnIce;
}
bool Tank::getIsOnIce() const
{
	return m_isOnIce;
}