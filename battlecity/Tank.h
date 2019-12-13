#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Macros.h"

class Tank
{
private:

	Position m_tankPosition;
	char m_tankDirection;
	float m_tankSpeed;

public:
	Tank();
	~Tank();
	Tank(float posX, float posY);

	sf::Texture m_tankTexture;
	sf::Texture getTexture();
};

