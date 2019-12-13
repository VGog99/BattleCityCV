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
	setUpTextures();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				moveSprite(m_localPlayerSprite, DIR_UP);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				moveSprite(m_localPlayerSprite, DIR_DOWN);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				moveSprite(m_localPlayerSprite, DIR_LEFT);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				moveSprite(m_localPlayerSprite, DIR_RIGHT);
			}
		}

		window.clear();

		//draw stuff
		window.draw(m_localPlayerSprite);
		//sf::FloatRect bounding_box = m_localPlayerSprite.getGlobalBounds();
		//sf::RectangleShape tankRect;
		//tankRect.setSize(sf::Vector2f(bounding_box.width, bounding_box.height));
		//tankRect.setFillColor(sf::Color::Transparent);
		//tankRect.setOutlineColor(sf::Color::Red);
		//tankRect.setPosition(sf::Vector2f(bounding_box.left, bounding_box.top));
		//tankRect.setOutlineThickness(2.f);
		//window.draw(tankRect);

		for (auto entity : m_worldEntities) {
			window.draw(entity->getSprite());
	/*		sf::FloatRect bounding_box = entity->getSprite().getGlobalBounds();
			sf::RectangleShape rect;
			rect.setSize(sf::Vector2f(bounding_box.width, bounding_box.height));
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineColor(sf::Color::Red);
			rect.setPosition(sf::Vector2f(bounding_box.left, bounding_box.top));
			rect.setOutlineThickness(2.f);*/
			//window.draw(rect);
		}

		window.display();
	}
}

void Engine::moveSprite(sf::Sprite& spriteToMove, const char direction)
{

	switch (direction) {
	case DIR_UP:
		
		if (handleCollision(m_localPlayerSprite))
			return;

		spriteToMove.move(0, -2);

		if (spriteToMove.getRotation() != 0)
			spriteToMove.setRotation(0.f);

		break;

	case DIR_DOWN:

		if (handleCollision(m_localPlayerSprite))
			return;

		spriteToMove.move(0, 2);

		if (spriteToMove.getRotation() != 180)
			spriteToMove.setRotation(180.f);

		break;

	case DIR_LEFT:

		if (handleCollision(m_localPlayerSprite))
			return;

		spriteToMove.move(-2, 0);

		if (spriteToMove.getRotation() != -90)
			spriteToMove.setRotation(-90.f);

		break;

	case DIR_RIGHT:

		if (handleCollision(m_localPlayerSprite))
			return;

		spriteToMove.move(2, 0);

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

		//if (firstSprite.getPosition().x < entity->getSprite().getPosition().x + secondSpriteBounds.width &&
		//	firstSprite.getPosition().x + firstSpriteBounds.width > entity->getSprite().getPosition().x &&
		//	firstSprite.getPosition().y < entity->getSprite().getPosition().y + secondSpriteBounds.height &&
		//	firstSpriteBounds.height + firstSprite.getPosition().y > entity->getSprite().getPosition().y) {
		//	firstSprite.setPosition(lastNonCollidedPosition.first, lastNonCollidedPosition.second);
		//	return true;
		//}

		if (firstSpriteBounds.intersects(secondSpriteBounds)) {
			firstSprite.setPosition(lastNonCollidedPosition.first, lastNonCollidedPosition.second);
			return true;
		}
	}

	lastNonCollidedPosition.first = firstSprite.getPosition().x;
	lastNonCollidedPosition.second = firstSprite.getPosition().y;
	return false;
}

void Engine::setUpTextures()
{
	m_localPlayerSprite.setTexture(m_localPlayerTank->m_tankTexture);
	m_localPlayerSprite.setOrigin(sf::Vector2f(m_localPlayerTank->m_tankTexture.getSize().x * 0.5, m_localPlayerTank->m_tankTexture.getSize().y * 0.5));
	//m_localPlayerSprite.setPosition(100.f, 100.f);
	m_localPlayerSprite.setPosition(m_localPlayerTank->getPosition().first, m_localPlayerTank->getPosition().second);

	//m_worldEntities.push_back(new WorldEntity(entityType::Brick, 50.f, 50.f));
	//m_worldEntities.push_back(new WorldEntity(entityType::Steel, 150.f, 50.f));
	//m_worldEntities.push_back(new WorldEntity(entityType::Ice, 200.f, 50.f));
	//m_worldEntities.push_back(new WorldEntity(entityType::Bush, 250.f, 50.f));

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
			}

			x++;
		}
		y++;
	}
}
