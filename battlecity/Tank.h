#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Macros.h"

class Tank
{
protected:

	Position m_tankPosition;
	Position m_tankLastNonCollidedPosition;
	char m_tankDirection = DIR_UP;
	float m_tankSpeed = 1.f;

public:
	Tank();
	~Tank();
	Tank(float posX, float posY);
	
	sf::Texture m_tankTexture;
	sf::Sprite m_tankSprite;
	
	Position getPosition() const;
	char getTankDirection();
	void setTankDirection(char direction);
	
	Position getLastNonCollidedPosition() const;
	void setLastNonCollidedPosition(const Position lastNonCollidedPosition);
	
	float getTankSpeed();
	void setTankSpeed(float speed);

};

