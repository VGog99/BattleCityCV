#include "Enemy.h"
#include "Engine.h"
#include <ctime>


Enemy::Enemy()
{
}

Enemy::Enemy(float posX, float posY)
{
	m_tankPosition = std::make_pair(posX, posY);
	m_tankTexture.loadFromFile("../resources/enemy.png");
	m_tankSprite.setTexture(m_tankTexture);
	m_tankTexture.setSmooth(true);
	m_tankSprite.setOrigin(sf::Vector2f(m_tankTexture.getSize().x * 0.5, m_tankTexture.getSize().y * 0.5));
	m_tankSprite.setPosition(m_tankPosition.first, m_tankPosition.second);
}

void Enemy::doMovement()
{
	if (!gameEngine.moveTank(this, m_tankDirection, m_enemySpeed)) {
		m_tankDirection = (char)(std::rand() % 4 + 48);
	}
}

float Enemy::getEnemySpeed()
{
	return m_enemySpeed;
}
