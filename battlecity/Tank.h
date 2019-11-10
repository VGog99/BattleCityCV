#pragma once
#include <SFML/Graphics.hpp>

class Tank
{
private:

	int speed;
	int damage;
	sf::Texture tankTexture;

public: 

	double posX;
	double posY;
	int direction;

	Tank(); //constructor default
	Tank(double posX, double posY, int speed ,int damage, int direction); //constructor cu parametrii
	sf::Sprite createSprite();

};

