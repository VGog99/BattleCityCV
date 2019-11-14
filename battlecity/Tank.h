#pragma once
#include <SFML/Graphics.hpp>

class Tank
{
private:

	unsigned int m_speed;
	unsigned int m_damage;
	sf::Texture tankTexture;

public: 

	double posX;
	double posY;
	int direction;
	void setSpeed(unsigned int speed);
	unsigned int getSpeed() const;
	
	Tank(); //constructor default
	Tank(int posX, int posY, int speed ,int damage, int direction); //constructor cu parametrii
	sf::Sprite createSprite();

};

