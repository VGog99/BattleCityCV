#include "Player.h"

Player::Player() {};

Player::~Player() {};

void Player::setPlayerName(const std::string name) {
	m_name = name;
}

std::string Player::getPlayerName() const {
	return m_name;
}

void Player::setDirection(const uint8_t direction) {
	m_direction = direction;
}