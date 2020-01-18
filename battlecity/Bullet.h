#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML/Graphics.hpp>
#include "Macros.h"
#include "WorldEntity.h"
#include <algorithm>
#include "Enemy.h"

class Enemy;

class Bullet
{
protected:

	Position m_bulletPosition;
	char m_bulletDirection = DIR_UP;
	Tank* m_firedBy;
	bool firedByEnemy;

public:
	Bullet();
	~Bullet();
	Bullet(Position position, char direction, Tank* firedBy, bool firedByEnemy);

	sf::Texture m_bulletTexture;
	sf::Sprite m_bulletSprite;

	Tank* getFiredBy() const;

	sf::Texture getTexture();
	Position getPosition() const;
	bool handleBullet(std::vector<std::unique_ptr<Bullet>>& bullets, std::vector<std::unique_ptr<WorldEntity>>& worldEntities, std::vector<std::unique_ptr<Enemy>>& enemyTanks, bool& wallHit, bool& tankHit, bool& solidHit);

};

