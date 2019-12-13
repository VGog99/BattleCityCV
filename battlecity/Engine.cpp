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

	sf::RenderWindow window(sf::VideoMode(730, 730), "World of Tanks Vaslui");
	setUpWorld();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				moveSprite(m_localPlayerTank->m_tankSprite, DIR_UP);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				moveSprite(m_localPlayerTank->m_tankSprite, DIR_DOWN);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				moveSprite(m_localPlayerTank->m_tankSprite, DIR_LEFT);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				moveSprite(m_localPlayerTank->m_tankSprite, DIR_RIGHT);
			}
		}

		window.clear();

		//draw stuff
		window.draw(m_localPlayerTank->m_tankSprite);
		
		//draw enemies
		for (auto enemyTank : m_enemyTanks) {
			window.draw(enemyTank->m_tankSprite);
		}

		//draw world entities
		for (auto entity : m_worldEntities) {
			window.draw(entity->getSprite());
		}

		window.display();
	}
}

void Engine::moveSprite(sf::Sprite& spriteToMove, const char direction)
{

	switch (direction) {
	case DIR_UP:
		
		if (handleCollision(spriteToMove))
			return;

		spriteToMove.move(0, -3);

		if (spriteToMove.getRotation() != 0)
			spriteToMove.setRotation(0.f);

		break;

	case DIR_DOWN:

		if (handleCollision(spriteToMove))
			return;

		spriteToMove.move(0, 3);

		if (spriteToMove.getRotation() != 180)
			spriteToMove.setRotation(180.f);

		break;

	case DIR_LEFT:

		if (handleCollision(spriteToMove))
			return;

		spriteToMove.move(-3, 0);

		if (spriteToMove.getRotation() != -90)
			spriteToMove.setRotation(-90.f);

		break;

	case DIR_RIGHT:

		if (handleCollision(spriteToMove))
			return;

		spriteToMove.move(3, 0);

		if (spriteToMove.getRotation() != 90)
			spriteToMove.setRotation(90.f);

		break;

	}
}

bool Engine::handleCollision(sf::Sprite& firstSprite)
{
	sf::FloatRect firstSpriteBounds = firstSprite.getGlobalBounds();
	static Position lastNonCollidedPosition;

	for (auto entity : m_worldEntities) {

		if (entity->getType() == entityType::Bush)
			continue;

		sf::FloatRect secondSpriteBounds = entity->getSprite().getGlobalBounds();

		if (firstSpriteBounds.intersects(secondSpriteBounds)) {
			firstSprite.setPosition(lastNonCollidedPosition.first, lastNonCollidedPosition.second);
			return true;
		}
	}

	for (auto enemyTank : m_enemyTanks) {

		if (firstSprite.getPosition() == enemyTank->m_tankSprite.getPosition())
			continue;

		sf::FloatRect secondSpriteBounds = enemyTank->m_tankSprite.getGlobalBounds();

		if (firstSpriteBounds.intersects(secondSpriteBounds)) {
			firstSprite.setPosition(lastNonCollidedPosition.first, lastNonCollidedPosition.second);
			return true;
		}
	}

	lastNonCollidedPosition.first = firstSprite.getPosition().x;
	lastNonCollidedPosition.second = firstSprite.getPosition().y;
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
