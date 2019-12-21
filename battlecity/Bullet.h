#pragma once
#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML/Graphics.hpp>
#include "Macros.h"
#include "WorldEntity.h"
#include "Enemy.h"
#include <algorithm>

class Bullet
{
protected:

	Position m_bulletPosition;
	char m_bulletDirection = DIR_UP;

public:
	Bullet();
	~Bullet();
	Bullet(Position position, char direction);

	sf::Texture m_bulletTexture;
	sf::Sprite m_bulletSprite;
	sf::Texture getTexture();
	Position getPosition() const;
	bool handleBullet(std::vector<std::unique_ptr<Bullet>>& bullets, std::vector<WorldEntity*>& worldEntities, std::vector<Enemy*>& m_enemyTanks);

};

