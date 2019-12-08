#include "Tank.h"
#include <iostream>
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

std::string Tank::getTileUnderTank() const
{
	return m_tileUnderTank;
}

void Tank::setTileUnderTank(const std::string tileUnderTank)
{
	m_tileUnderTank = tileUnderTank;
}

bool Tank::movePlayerTank(std::vector<std::unique_ptr<Object>>& boardVec, position from, position to, char direction)
{
	((Tank*)boardVec.at(from.first * MATRIX_SIZE + from.second).get())->setDirection(direction);

	if ((((Tank*)boardVec.at(from.first * MATRIX_SIZE + from.second).get())->getTileUnderTank() == "road" && 
		boardVec.at(to.first * MATRIX_SIZE + to.second)->getType() == "road") || 
		(((Tank*)boardVec.at(from.first * MATRIX_SIZE + from.second).get())->getTileUnderTank() == "ice" &&
		boardVec.at(to.first * MATRIX_SIZE + to.second)->getType() == "ice") ||
		(((Tank*)boardVec.at(from.first * MATRIX_SIZE + from.second).get())->getTileUnderTank() == "bush" &&
		boardVec.at(to.first * MATRIX_SIZE + to.second)->getType() == "bush")) {

		std::swap(boardVec.at(from.first * MATRIX_SIZE + from.second), boardVec.at(to.first * MATRIX_SIZE + to.second));
		return true;
	}
	else 
	if (((Tank*)boardVec.at(from.first * MATRIX_SIZE + from.second).get())->getTileUnderTank() == "bush" &&
		boardVec.at(to.first * MATRIX_SIZE + to.second)->getType() == "road") {
		
		std::swap(boardVec.at(from.first * MATRIX_SIZE + from.second), boardVec.at(to.first * MATRIX_SIZE + to.second));
		boardVec.at(from.first * MATRIX_SIZE + from.second) = std::make_unique<Bush>();
		((Tank*)boardVec.at(to.first * MATRIX_SIZE + to.second).get())->setTileUnderTank("road");
		((Tank*)boardVec.at(to.first * MATRIX_SIZE + to.second).get())->setIsHidden(false);
		return true;
	}
	else
	if (((Tank*)boardVec.at(from.first * MATRIX_SIZE + from.second).get())->getTileUnderTank() == "road" &&
		boardVec.at(to.first * MATRIX_SIZE + to.second)->getType() == "bush") {

		std::swap(boardVec.at(from.first * MATRIX_SIZE + from.second), boardVec.at(to.first * MATRIX_SIZE + to.second));
		boardVec.at(from.first * MATRIX_SIZE + from.second) = std::make_unique<Road>();
		((Tank*)boardVec.at(to.first * MATRIX_SIZE + to.second).get())->setTileUnderTank("bush");
		((Tank*)boardVec.at(to.first * MATRIX_SIZE + to.second).get())->setIsHidden(true);
		return true;
	}
	else
	if (((Tank*)boardVec.at(from.first * MATRIX_SIZE + from.second).get())->getTileUnderTank() == "ice" &&
		boardVec.at(to.first * MATRIX_SIZE + to.second)->getType() == "road") {

		std::swap(boardVec.at(from.first * MATRIX_SIZE + from.second), boardVec.at(to.first * MATRIX_SIZE + to.second));
		boardVec.at(from.first * MATRIX_SIZE + from.second) = std::make_unique<Ice>();
		((Tank*)boardVec.at(to.first * MATRIX_SIZE + to.second).get())->setTileUnderTank("road");
		((Tank*)boardVec.at(to.first * MATRIX_SIZE + to.second).get())->setIsOnIce(false);
		return true;
	}
	else
	if (((Tank*)boardVec.at(from.first * MATRIX_SIZE + from.second).get())->getTileUnderTank() == "road" &&
		boardVec.at(to.first * MATRIX_SIZE + to.second)->getType() == "ice") {

		std::swap(boardVec.at(from.first * MATRIX_SIZE + from.second), boardVec.at(to.first * MATRIX_SIZE + to.second));
		boardVec.at(from.first * MATRIX_SIZE + from.second) = std::make_unique<Road>();
		((Tank*)boardVec.at(to.first * MATRIX_SIZE + to.second).get())->setTileUnderTank("ice");
		((Tank*)boardVec.at(to.first * MATRIX_SIZE + to.second).get())->setIsOnIce(true);
		return true;
	}
	else
	if (((Tank*)boardVec.at(from.first * MATRIX_SIZE + from.second).get())->getTileUnderTank() == "ice" &&
		boardVec.at(to.first * MATRIX_SIZE + to.second)->getType() == "bush") {

		std::swap(boardVec.at(from.first * MATRIX_SIZE + from.second), boardVec.at(to.first * MATRIX_SIZE + to.second));
		boardVec.at(from.first * MATRIX_SIZE + from.second) = std::make_unique<Ice>();
		((Tank*)boardVec.at(to.first * MATRIX_SIZE + to.second).get())->setTileUnderTank("bush");
		((Tank*)boardVec.at(to.first * MATRIX_SIZE + to.second).get())->setIsHidden(true);
		((Tank*)boardVec.at(to.first * MATRIX_SIZE + to.second).get())->setIsOnIce(false);
		return true;
	}
	else
	if (((Tank*)boardVec.at(from.first * MATRIX_SIZE + from.second).get())->getTileUnderTank() == "bush" &&
		boardVec.at(to.first * MATRIX_SIZE + to.second)->getType() == "ice") {

		std::swap(boardVec.at(from.first * MATRIX_SIZE + from.second), boardVec.at(to.first * MATRIX_SIZE + to.second));
		boardVec.at(from.first * MATRIX_SIZE + from.second) = std::make_unique<Bush>();
		((Tank*)boardVec.at(to.first * MATRIX_SIZE + to.second).get())->setTileUnderTank("ice");
		((Tank*)boardVec.at(to.first * MATRIX_SIZE + to.second).get())->setIsHidden(false);
		((Tank*)boardVec.at(to.first * MATRIX_SIZE + to.second).get())->setIsOnIce(true);
		return true;
	}

	return false;
}
