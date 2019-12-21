#pragma once
#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML/Graphics.hpp>
#include "Macros.h"

class Bullet
{
protected:

	Position m_bulletPosition;
	Position m_bulletLastNonCollidedPosition;
	char m_bulletDirection = DIR_UP;

public:
	Bullet();
	~Bullet();
	Bullet(float posX, float posY);

	sf::Texture m_bulletTexture;
	sf::Sprite m_bulletSprite;
	sf::Texture getTexture();
	Position getPosition() const;
	Position getLastNonCollidedPosition() const;
	void setLastNonCollidedPosition(const Position lastNonCollidedPosition);
};

