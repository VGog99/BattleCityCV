#include "WorldEntity.h"

WorldEntity::WorldEntity(entityType type, float posX, float posY) : m_entityType(type), m_entityPosition(std::make_pair(posX, posY))
{
	switch (type) {
		case entityType::Brick: {
			m_worldEntityTexture.loadFromFile("../resources/brick.png");
			m_isDamageable = true;
			break;
		}
		case entityType::Steel: {
			m_worldEntityTexture.loadFromFile("../resources/steel.png");
			break;
		}
		case entityType::Bush: {
			m_worldEntityTexture.loadFromFile("../resources/bush.png");
			break;
		}
		case entityType::Eagle: {
			m_worldEntityTexture.loadFromFile("../resources/eagle.png");
			break;
		}
		case entityType::Ice: {
			m_worldEntityTexture.loadFromFile("../resources/ice.png");
			break;
		}
		case entityType::Water: {
			m_worldEntityTexture.loadFromFile("../resources/water.png");
			break;
		}
	}

	m_worldEntitySprite.setTexture(m_worldEntityTexture);
	m_worldEntitySprite.setOrigin(sf::Vector2f(m_worldEntityTexture.getSize().x * 0.5, m_worldEntityTexture.getSize().y * 0.5));
	m_worldEntitySprite.setPosition(m_entityPosition.first, m_entityPosition.second);
}

entityType WorldEntity::getType() const
{
	return m_entityType;
}

sf::Sprite WorldEntity::getSprite() const
{
	return m_worldEntitySprite;
}