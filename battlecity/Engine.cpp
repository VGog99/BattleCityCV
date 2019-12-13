#include "Engine.h"
#include "Tank.h"
#include "Macros.h"

Engine::Engine()
{

}

Engine::~Engine()
{
}

void Engine::runGame() {

	sf::RenderWindow window(sf::VideoMode(600, 600), "World of Tanks Vaslui");
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
		window.draw(testSprite);

		for (auto entity : m_worldEntities) {
			window.draw(entity.getSprite());
		}

		window.display();
	}
}

void Engine::moveSprite(sf::Sprite& spriteToMove, const char direction)
{

	switch (direction) {
	case DIR_UP:

		handleCollision(m_localPlayerSprite, testSprite);
		spriteToMove.move(0, -2);

		if (spriteToMove.getRotation() != 0)
			spriteToMove.setRotation(0.f);

		break;

	case DIR_DOWN:
		
		handleCollision(m_localPlayerSprite, testSprite);
		spriteToMove.move(0, 2);

		if (spriteToMove.getRotation() != 180)
			spriteToMove.setRotation(180.f);

		break;

	case DIR_LEFT:
		
		handleCollision(m_localPlayerSprite, testSprite);
		spriteToMove.move(-2, 0);

		if (spriteToMove.getRotation() != -90)
			spriteToMove.setRotation(-90.f);

		break;

	case DIR_RIGHT:
		
		handleCollision(m_localPlayerSprite, testSprite);
		spriteToMove.move(2, 0);

		if (spriteToMove.getRotation() != 90)
			spriteToMove.setRotation(90.f);

		break;

	}
}

void Engine::handleCollision(sf::Sprite& firstSprite, sf::Sprite secondSprite)
{
	sf::FloatRect firstSpriteBounds = firstSprite.getGlobalBounds();
	sf::FloatRect secondSpriteBounds = secondSprite.getGlobalBounds();
	static Position lastNonCollidedPosition;

	if (!(firstSprite.getPosition().x < secondSprite.getPosition().x + secondSpriteBounds.width &&
		firstSprite.getPosition().x + firstSpriteBounds.width > secondSprite.getPosition().x &&
		firstSprite.getPosition().y < secondSprite.getPosition().y + secondSpriteBounds.height &&
		firstSpriteBounds.height + firstSprite.getPosition().y > secondSprite.getPosition().y))
	{
		lastNonCollidedPosition.first = firstSprite.getPosition().x;
		lastNonCollidedPosition.second = firstSprite.getPosition().y;
	}
	else
	{
		firstSprite.setPosition(lastNonCollidedPosition.first, lastNonCollidedPosition.second);
	}
}

void Engine::setUpTextures()
{
	m_localPlayerSprite.setTexture(m_localPlayerTank->m_tankTexture);
	m_localPlayerSprite.setOrigin(sf::Vector2f(m_localPlayerTank->m_tankTexture.getSize().x * 0.5, m_localPlayerTank->m_tankTexture.getSize().y * 0.5));
	m_localPlayerSprite.setPosition(100.f, 100.f);

	testSprite.setTexture(m_localPlayerTank->m_tankTexture);
	testSprite.setOrigin(sf::Vector2f(m_localPlayerTank->m_tankTexture.getSize().x * 0.5, m_localPlayerTank->m_tankTexture.getSize().y * 0.5));

	testSprite.setPosition(200.f, 200.f);

	m_worldEntities.emplace_back(entityType::Brick, 50.f, 50.f);
}
