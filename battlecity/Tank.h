#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
class Tank : public Object
{
private:

	uint16_t m_speed;
	uint16_t m_damage;
	sf::Texture tankTexture0;
	sf::Texture tankTexture1;
	sf::Texture tankTexture2;
	sf::Texture tankTexture3;

public: 

	using position = std::pair<double, double>;
	position pos;
	uint16_t m_direction;
	void setSpeed(uint16_t speed);
	uint16_t getSpeed() const;
	Tank(); //constructor default
	Tank(double posX, double posY, uint16_t speed ,uint16_t damage, uint16_t direction); //constructor cu parametrii
	sf::Sprite createSprite(int pos);


};

