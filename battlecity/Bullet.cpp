#include "Bullet.h"


Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

Bullet::Bullet(Position position, char direction, Tank* firedBy) : m_bulletPosition(position), m_bulletDirection(direction), m_firedBy(firedBy)
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

Tank* Bullet::getFiredBy() const
{
	return m_firedBy;
}

sf::Texture Bullet::getTexture()
{
	return m_bulletTexture;
}

Position Bullet::getPosition() const
{
	return m_bulletPosition;
}

bool Bullet::handleBullet(std::vector<std::unique_ptr<Bullet>>& bullets, std::vector<std::unique_ptr<WorldEntity>>& worldEntities, std::vector<std::unique_ptr<Enemy>>& enemyTanks, const Tank* localPlayerTank)
{
	switch (m_bulletDirection) {
		case DIR_UP: this->m_bulletSprite.move(0, -5); break;
		case DIR_DOWN: this->m_bulletSprite.move(0, 5); break;
		case DIR_LEFT: this->m_bulletSprite.move(-5, 0); break;
		case DIR_RIGHT: this->m_bulletSprite.move(5, 0); break;
	}

	sf::FloatRect bulletSpriteBounds = this->m_bulletSprite.getGlobalBounds();
	auto bulletItr = std::find_if(bullets.begin(), bullets.end(), [this](std::unique_ptr<Bullet>& element) {return this == element.get(); });

	for (auto &entity : worldEntities) {

		if (entity->getType() == entityType::Bush)
			continue;
		if (entity->getType() == entityType::Ice)
			continue;
		if (entity->getType() == entityType::Water)
			continue;

		sf::FloatRect worldEntitySpriteBounds = entity->getSprite().getGlobalBounds();
		auto worldEntityItr = std::find_if(worldEntities.begin(), worldEntities.end(), [&entity](std::unique_ptr<WorldEntity>& element) {return entity == element; });

		if (bulletSpriteBounds.intersects(worldEntitySpriteBounds)) {

			bullets.erase(bulletItr);
	
			if (entity->getType() == entityType::Brick)
				worldEntities.erase(worldEntityItr);

			return false;
		}
	}

	for (auto &enemy : enemyTanks) {

		if (m_firedBy == enemy.get())
			continue;

		sf::FloatRect enemySpriteBounds = enemy->m_tankSprite.getGlobalBounds();
		auto enemyItr = std::find_if(enemyTanks.begin(), enemyTanks.end(), [&enemy](std::unique_ptr<Enemy>& element) {return enemy == element; });
		
		if (bulletSpriteBounds.intersects(enemySpriteBounds)) {
			bullets.erase(bulletItr);
			enemyTanks.erase(enemyItr);

			return false;
		}
	}

	sf::FloatRect localPlayerBounds = localPlayerTank->m_tankSprite.getGlobalBounds();

	if (bulletSpriteBounds.intersects(localPlayerBounds)) {

		if (m_firedBy == localPlayerTank)
			return true;

		// to do: de implementat functionalitatea cand local player-ul este lovit (kill si scazut o viata)
		std::cout << "[!] Local player was shot! \n";
	}


	return true;
}


