#include "Player.h"

Player::Player() {};

Player::~Player() {};

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