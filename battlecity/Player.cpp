#include "Player.h"



Player::Player()
{
	playerTexture.loadFromFile("../resources/playerOne.png");
};

Player::Player(double posX, double posY, int speed, int damage, int direction) 
	:Tank(posX, posY, speed, damage, direction)
{

}

void Player::setPos(double pX, double pY)
{
	posX = pX;
	posY = pY;
}

double Player::getPosX()
{
	return posX;
}
double Player::getPosY()
{
	return posY;
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

std::string Player::getType() {
	return "player";
}