#include "Engine.h"
#include "Tank.h"
#include "Macros.h"
#include <fstream>

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::runGame() {

	sf::RenderWindow window(sf::VideoMode(720, 720), "World of Tanks Vaslui");
	window.setFramerateLimit(60);
	setUpWorld();

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				moveTank(m_localPlayerTank, DIR_UP);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				moveTank(m_localPlayerTank, DIR_DOWN);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				moveTank(m_localPlayerTank, DIR_LEFT);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				moveTank(m_localPlayerTank, DIR_RIGHT);
			}
		}

		window.clear();

		//draw stuff
		window.draw(m_localPlayerTank->m_tankSprite);
		
		//do movement and draw enemies
		for (auto enemyTank : m_enemyTanks) {
			enemyTank->doMovement();
			window.draw(enemyTank->m_tankSprite);
		}

		//draw world entities
		for (auto entity : m_worldEntities) {
			window.draw(entity->getSprite());
		}

		window.display();
	}
}

bool Engine::moveTank(Tank* tankToMove, const char direction)
{

	switch (direction) {
	case DIR_UP:
		
		if (handleCollision(tankToMove))
			return false;

		tankToMove->m_tankSprite.move(0, -3);

		if (tankToMove->m_tankSprite.getRotation() != 0)
			tankToMove->m_tankSprite.setRotation(0.f);
		
		break;

	case DIR_DOWN:

		if (handleCollision(tankToMove))
			return false;

		tankToMove->m_tankSprite.move(0, 3);

		if (tankToMove->m_tankSprite.getRotation() != 180)
			tankToMove->m_tankSprite.setRotation(180.f);

		break;

	case DIR_LEFT:

		if (handleCollision(tankToMove))
			return false;

		tankToMove->m_tankSprite.move(-3, 0);

		if (tankToMove->m_tankSprite.getRotation() != -90)
			tankToMove->m_tankSprite.setRotation(-90.f);

		break;

	case DIR_RIGHT:

		if (handleCollision(tankToMove))
			return false;

		tankToMove->m_tankSprite.move(3, 0);

		if (tankToMove->m_tankSprite.getRotation() != 90)
			tankToMove->m_tankSprite.setRotation(90.f);

		break;

	}

	// daca s-a executat miscarea, returnam true
	return true;
}

bool Engine::handleCollision(Tank* tankToCheck)
{
	sf::FloatRect firstSpriteBounds = tankToCheck->m_tankSprite.getGlobalBounds();

	for (auto entity : m_worldEntities) {

		if (entity->getType() == entityType::Bush)
			continue;

		sf::FloatRect secondSpriteBounds = entity->getSprite().getGlobalBounds();

		if (firstSpriteBounds.intersects(secondSpriteBounds)) {
			tankToCheck->m_tankSprite.setPosition(tankToCheck->getLastNonCollidedPosition().first, tankToCheck->getLastNonCollidedPosition().second);
			return true;
		}
	}

	for (auto enemyTank : m_enemyTanks) {

		if (tankToCheck == enemyTank)
			continue;

		sf::FloatRect secondSpriteBounds = enemyTank->m_tankSprite.getGlobalBounds();

		if (firstSpriteBounds.intersects(secondSpriteBounds)) {
			tankToCheck->m_tankSprite.setPosition(tankToCheck->getLastNonCollidedPosition().first, tankToCheck->getLastNonCollidedPosition().second);
			return true;
		}
	}

	if (tankToCheck != m_localPlayerTank) {
		if (firstSpriteBounds.intersects(m_localPlayerTank->m_tankSprite.getGlobalBounds())) {
			tankToCheck->m_tankSprite.setPosition(tankToCheck->getLastNonCollidedPosition().first, tankToCheck->getLastNonCollidedPosition().second);
			return true;
		}
	}

	tankToCheck->setLastNonCollidedPosition(std::make_pair(tankToCheck->m_tankSprite.getPosition().x, tankToCheck->m_tankSprite.getPosition().y));
	return false;
}

void Engine::setUpWorld()
{
	unsigned short x = 0;
	unsigned short y = 0;

	std::string inputFromFile;
	std::ifstream file("../stages/stage1.txt");

	while (std::getline(file, inputFromFile)) {
		x = 0;
		for (auto chr : inputFromFile) {

			switch (chr) {
				case 'w': {

					m_worldEntities.push_back(new WorldEntity(entityType::WorldBound, x * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 2, y * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 2));
					break;
				}
				case 'b': {
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * WORLD_ENTITY_SIZE, y * WORLD_ENTITY_SIZE));
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 3, y * WORLD_ENTITY_SIZE));
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * WORLD_ENTITY_SIZE + 2 * (WORLD_ENTITY_SIZE / 3), y * WORLD_ENTITY_SIZE));
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * WORLD_ENTITY_SIZE, y * WORLD_ENTITY_SIZE + 2 * (WORLD_ENTITY_SIZE / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 3, y * WORLD_ENTITY_SIZE + 2 * (WORLD_ENTITY_SIZE / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * WORLD_ENTITY_SIZE + 2 * (WORLD_ENTITY_SIZE / 3), y * WORLD_ENTITY_SIZE + 2 * (WORLD_ENTITY_SIZE / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * WORLD_ENTITY_SIZE, y * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 3));
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 3, y * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 3));
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * WORLD_ENTITY_SIZE + 2 * (WORLD_ENTITY_SIZE / 3), y * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 3));
					break;
				}
				case 's': {
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * WORLD_ENTITY_SIZE, y * WORLD_ENTITY_SIZE));
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 3, y * WORLD_ENTITY_SIZE));
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * WORLD_ENTITY_SIZE + 2 * (WORLD_ENTITY_SIZE / 3), y * WORLD_ENTITY_SIZE));
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * WORLD_ENTITY_SIZE, y * WORLD_ENTITY_SIZE + 2 * (WORLD_ENTITY_SIZE / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 3, y * WORLD_ENTITY_SIZE + 2 * (WORLD_ENTITY_SIZE / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * WORLD_ENTITY_SIZE + 2 * (WORLD_ENTITY_SIZE / 3), y * WORLD_ENTITY_SIZE + 2 * (WORLD_ENTITY_SIZE / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * WORLD_ENTITY_SIZE, y * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 3));
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 3, y * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 3));
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * WORLD_ENTITY_SIZE + 2 * (WORLD_ENTITY_SIZE / 3), y * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 3));					break;
				}
				case 'e': {
					m_worldEntities.push_back(new WorldEntity(entityType::Eagle, x * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 2, y * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 2));

					break;
				}
				case ' ': {

					break;
				}
				case 'g': {
					m_worldEntities.push_back(new WorldEntity(entityType::Bush, x * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 2, y * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 2));
					break;
				}
				case 'i': {
					m_worldEntities.push_back(new WorldEntity(entityType::Ice, x * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 2, y * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 2));
					break;
				}
				case 'a': {
					m_worldEntities.push_back(new WorldEntity(entityType::Water, x * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 2, y * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 2));
					break;
				}
				case 'h': {
					m_enemyTanks.push_back(new Enemy(x * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 2, y * WORLD_ENTITY_SIZE + WORLD_ENTITY_SIZE / 2));
				}
			}

			x++;
		}
		y++;
	}
}
