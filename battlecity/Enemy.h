#pragma once
#include "Tank.h"
#include "Bullet.h"

class Enemy : public Tank
{
protected:

	float m_enemySpeed = 1.2f;
	float secondCounter = 0.f;

public:
	Enemy();
	Enemy(float posX, float posY);

	void fireBullet(std::vector<std::unique_ptr<Bullet>>& m_bulletVec, sf::Time elapsed);
	void doMovement();
	float getEnemySpeed();
	void setEnemySpeed(float speed);
	bool isEnemy() const;
};

