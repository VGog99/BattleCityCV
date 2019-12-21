#include "Bullet.h"


Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

Bullet::Bullet(Position position, char direction): m_bulletPosition(position), m_bulletDirection(direction)
{
	m_bulletTexture.loadFromFile("../resources/bullet.png");
	m_bulletSprite.setTexture(m_bulletTexture);
	m_bulletTexture.setSmooth(true);
	m_bulletSprite.setOrigin(sf::Vector2f(m_bulletTexture.getSize().x * 0.5, m_bulletTexture.getSize().y * 0.5));
	m_bulletSprite.setPosition(m_bulletPosition.first, m_bulletPosition.second);

	switch (direction) {
	case DIR_UP: m_bulletSprite.setRotation(0.f); break;
	case DIR_DOWN: m_bulletSprite.setRotation(180.f); break;
	case DIR_LEFT: m_bulletSprite.setRotation(-90.f); break;
	case DIR_RIGHT:	m_bulletSprite.setRotation(90.f); break;
	}
}

sf::Texture Bullet::getTexture()
{
	return m_bulletTexture;
}

Position Bullet::getPosition() const
{
	return m_bulletPosition;
}

bool Bullet::handleBullet(std::vector<std::unique_ptr<Bullet>>& bullets, std::vector<WorldEntity*>& worldEntities, std::vector<Enemy*>& m_enemyTanks)
{
	switch (m_bulletDirection) {
		case DIR_UP: this->m_bulletSprite.move(0, -1); break;
		case DIR_DOWN: this->m_bulletSprite.move(0, 1); break;
		case DIR_LEFT: this->m_bulletSprite.move(-1, 0); break;
		case DIR_RIGHT: this->m_bulletSprite.move(1, 0); break;
	}

	sf::FloatRect bulletSpriteBounds = this->m_bulletSprite.getGlobalBounds();

	for (auto entity : worldEntities) {

		if (entity->getType() == entityType::Bush)
			continue;
		if (entity->getType() == entityType::Ice)
			continue;
		if (entity->getType() == entityType::Water)
			continue;

		sf::FloatRect worldEntitySpriteBounds = entity->getSprite().getGlobalBounds();
		auto itr = std::find_if(bullets.begin(), bullets.end(), [this](std::unique_ptr<Bullet>& element) {return this == element.get(); });

		if (bulletSpriteBounds.intersects(worldEntitySpriteBounds)) {

			bullets.erase(itr);

			return false;
		}
	}

	return true;
}


