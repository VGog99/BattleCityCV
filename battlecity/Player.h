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
	
	Player(double posX, double posY, int speed, int damage, int direction);
	sf::Sprite createSprite();
	void drawEnemy();

	std::string getPlayerName() const;
	void setPlayerName(const std::string name);
	
	void setPos(double pX, double pY);
	double getPosX();
	double getPosY();

	void setDirection(const char direction);
	char getDirection() const;

};

