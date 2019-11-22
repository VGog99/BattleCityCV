#include "Player.h"



Player::Player()
{
	playerTexture.loadFromFile("../resources/playerOne.png");
};

Player::Player(double posX, double posY, uint16_t speed, uint16_t damage, uint16_t direction) 
	:Tank(posX, posY, speed, damage, direction)
{

}

void Player::setPos(double pX, double pY)
{
	pos.first = pX;
	pos.second = pY;
}

double Player::getPosX() const
{
	return pos.first;
}
double Player::getPosY() const
{
	return pos.second;
}

void Player::setPlayerName(const std::string name) {
	m_name = name;
}

std::string Player::getPlayerName() const {
	return m_name;
}

void Player::setDirection(const char direction) {
	m_direction = direction;
}

char Player::getDirection() const {
	return m_direction;
}

sf::Sprite Player::createSprite()
{
	sf::Sprite sprite(playerTexture);
	return sprite;
}

std::string Player::getType() const {
	return "player";
}