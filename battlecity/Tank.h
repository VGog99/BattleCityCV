#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

using position = std::pair<double, double>;

class Tank : public Object
{

private:

	uint16_t m_speed;
	uint16_t m_damage;
	sf::Texture tankTexture;
	position m_position;
	char m_direction = '0';

public:

	void setSpeed(uint16_t speed);
	uint16_t getSpeed() const;
	Tank(); //constructor default
	Tank(double posX, double posY, uint16_t speed ,uint16_t damage, char direction); //constructor cu parametrii
	sf::Sprite createSprite();
	void setDirection(const char direction);
	std::string getType() const;
};

