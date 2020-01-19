#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Macros.h"

enum tankType {
	enemyTank,
	localPlayerTank
};

class Tank
{
public:
	Tank();
	~Tank();
	Tank(float posX, float posY);

	Position getPosition() const;
	char getTankDirection();
	void setTankDirection(char direction);

	float getTankSpeed();
	void setTankSpeed(float speed);
	virtual bool isEnemy() const;

public:
	sf::Texture m_tankTexture;
	sf::Sprite m_tankSprite;

protected:

	Position m_tankPosition;
	Position m_tankLastNonCollidedPosition;
	char m_tankDirection = DIR_UP;
	float m_tankSpeed = 1.7f;
};

