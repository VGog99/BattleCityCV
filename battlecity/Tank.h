#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Macros.h"

class Tank
{
protected:

	Position m_tankPosition;
	char m_tankDirection;
	float m_tankSpeed;

public:
	Tank();
	~Tank();
	Tank(float posX, float posY);

	sf::Texture m_tankTexture;
	sf::Sprite m_tankSprite;
	sf::Texture getTexture();
	Position getPosition() const;
};

