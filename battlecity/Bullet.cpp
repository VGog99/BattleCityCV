#include "Engine.h"
#include "Bullet.h"


Bullet::Bullet()
{
}

Bullet::~Bullet()
{
	AnimatedSprite explosion(sf::seconds(0.1), true, false);
	explosion.setPosition(this->m_bulletSprite.getPosition().x, this->m_bulletSprite.getPosition().y);
	explosion.setOrigin(sf::Vector2f(24, 24));
	explosion.play(gameEngine.explosionAnim);
	gameEngine.explosionsVec.push_back(explosion);
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

bool Bullet::handleBullet(std::vector<std::unique_ptr<Bullet>>& bullets, std::vector<std::unique_ptr<WorldEntity>>& worldEntities, std::vector<std::unique_ptr<Enemy>>& enemyTanks, Tank* firingTank, bool& wallHit, bool& enemyHit)
{
	switch (m_bulletDirection)
	{
		case DIR_UP: this->m_bulletSprite.move(0, -5); break;
		case DIR_DOWN: this->m_bulletSprite.move(0, 5); break;
		case DIR_LEFT: this->m_bulletSprite.move(-5, 0); break;
		case DIR_RIGHT: this->m_bulletSprite.move(5, 0); break;
	}

	sf::FloatRect bulletSpriteBounds = this->m_bulletSprite.getGlobalBounds();
	auto bulletItr = std::find_if(bullets.begin(), bullets.end(), [this](std::unique_ptr<Bullet>& element) {return this == element.get(); });

	std::vector<std::unique_ptr<WorldEntity>>::iterator it;

	for (it = worldEntities.begin(); it < worldEntities.end(); it++) {

			if (it->get()->getType() == entityType::Bush)
				continue;
			if (it->get()->getType() == entityType::Ice)
				continue;
			if (it->get()->getType() == entityType::Water)
				continue;

			sf::FloatRect worldEntitySpriteBounds = it->get()->getSprite().getGlobalBounds();
			
			if (bulletSpriteBounds.intersects(worldEntitySpriteBounds)) {

				bullets.erase(bulletItr);

				if (it->get()->getType() == entityType::Brick)
				{
					worldEntities.erase(it);
					wallHit = true;
				}
				else if (it->get()->getType() == entityType::Eagle)
				{
					worldEntities.erase(it);
					gameEngine.setGameOver(true);
				}

				return false;
			}
	}

	for (auto &enemy : enemyTanks) {

		if (firingTank != nullptr && firingTank->isEnemy())
			break;

		sf::FloatRect enemySpriteBounds = enemy->m_tankSprite.getGlobalBounds();
		auto enemyItr = std::find_if(enemyTanks.begin(), enemyTanks.end(), [&enemy](std::unique_ptr<Enemy>& element) {return enemy == element; });
		
		if (bulletSpriteBounds.intersects(enemySpriteBounds)) {
			enemyHit = true;
			bullets.erase(bulletItr);
			enemyTanks.erase(enemyItr);
			gameEngine.setlocalPlayerKills(gameEngine.getLocalPlayerKills() + 1);
			return false;
		}
	}

	sf::FloatRect localPlayerBounds = gameEngine.m_localPlayerTank->m_tankSprite.getGlobalBounds();

	if (bulletSpriteBounds.intersects(localPlayerBounds)) {

		if (firingTank != nullptr && !firingTank->isEnemy())
			return true;

		if (gameEngine.m_localPlayerLives[0] == 0) {
			gameEngine.setGameOver(true);
			return true;
		}

		gameEngine.m_localPlayerLives[0]--;
		
		// to do: de implementat functionalitatea cand local player-ul este lovit (kill si scazut o viata)
		std::cout << "[!] Local player was shot! \n";
		bullets.erase(bulletItr);
		return false;
	}

	return true;
}


