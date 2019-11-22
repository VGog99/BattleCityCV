#pragma once
#include <string>
#include "SDK.h"

class Player: public Tank
{
private:
	std::string m_name;	
	char m_direction;
	sf::Texture playerTexture;

public:
	Player();
	
	Player(double posX, double posY, uint16_t speed, uint16_t damage, uint16_t direction);
	sf::Sprite createSprite();
	void drawEnemy();
	std::string getPlayerName() const;
	void setPlayerName(const std::string name);
	
	void setPos(double pX, double pY);
	double getPosX() const;
	double getPosY() const;

	void setDirection(const char direction);
	char getDirection() const;
	std::string getType() const;

};

