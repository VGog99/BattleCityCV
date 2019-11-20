#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
class Tank : public Object
{
private:

	unsigned int m_speed;
	unsigned int m_damage;
	sf::Texture tankTexture0;
	sf::Texture tankTexture1;
	sf::Texture tankTexture2;
	sf::Texture tankTexture3;

public: 

	double posX;
	double posY;
	int direction;
	void setSpeed(unsigned int speed);
	unsigned int getSpeed() const;
	
	Tank(); //constructor default
	Tank(double posX, double posY, int speed ,int damage, int direction); //constructor cu parametrii
	sf::Sprite createSprite(int pos);


};

