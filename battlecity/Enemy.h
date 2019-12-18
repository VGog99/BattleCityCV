#pragma once
#include "Tank.h"

class Enemy : public Tank
{
protected:

	float m_enemySpeed = 2.0f;

public:
	Enemy();
	Enemy(float posX, float posY);

	void doMovement();

	float getEnemySpeed();
	void setEnemySpeed(float speed);
};

