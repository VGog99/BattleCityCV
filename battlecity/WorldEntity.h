#pragma once
#include <SFML\Graphics.hpp>
#include "Macros.h"

enum entityType {
	Brick,
	Steel,
	Bush,
	Water,
	Ice,
	Eagle,
	WorldBound
};

class WorldEntity
{

private:
	sf::Texture m_worldEntityTexture;
	sf::Sprite m_worldEntitySprite;
	entityType m_entityType;
	bool m_isDamageable;
	Position m_entityPosition;

public:
	WorldEntity(entityType type, float posX, float posY);
	entityType getType() const;

	sf::Sprite getSprite() const;
};

