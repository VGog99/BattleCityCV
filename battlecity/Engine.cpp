#include "Engine.h"
#include "Tank.h"
#include "Macros.h"
#include <fstream>

std::ofstream logFile("log.log", std::ios::app);
Logger logger(std::cout, Logger::Level::Info);

Engine::Engine()
{
	m_gameOver = false;
	m_gameStarted = false;
	m_localPlayerKills = 0;
}

Engine::~Engine()
{
}

void Engine::runGame() {

	Menu menu;

	sf::Music menuMusic;

	if (!menuMusic.openFromFile("../resources/menumusic.wav"))
		logger.Logi("Nu s-a putut incarca fisierul de muzica.");

	menuMusic.setVolume(0.60f);
	menuMusic.play();

	int savedMenuOption = menu.getMenuOption();

	sf::RenderWindow window(sf::VideoMode(720, 720), "World of Tanks Vaslui");
	window.setFramerateLimit(60);

	// load map
	setUpWorld();

	while (window.isOpen())
	{
		if (menu.getIsInMenu()) {
			menu.updateMenuColor();
		}

		sf::Event event;
		while (window.pollEvent(event))
		{

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

				if (menu.getIsInMenu()) {
					savedMenuOption = menu.getMenuOption();
					savedMenuOption--;
					savedMenuOption = std::clamp(savedMenuOption, 0, 1);
					menu.setMenuOption(savedMenuOption);
				}

				m_localPlayerTank->setTankDirection(DIR_UP);
				logger.Logi("The player is moving upwards");
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				
				if (menu.getIsInMenu()) {
					savedMenuOption = menu.getMenuOption();
					savedMenuOption++;
					savedMenuOption = std::clamp(savedMenuOption, 0, 1);
					menu.setMenuOption(savedMenuOption);
				}

				m_localPlayerTank->setTankDirection(DIR_DOWN);
				logger.Logi("The player moved downwards");
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

				m_localPlayerTank->setTankDirection(DIR_LEFT);
				logger.Logi("The player moved to the left");
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

				m_localPlayerTank->setTankDirection(DIR_RIGHT);
				logger.Logi("The player moved to the right");
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

				if (!menu.getMenuOption())
				{
					logger.Logi("Game started");
					menu.setIsInMenu(false);
				}
				else
				{
					logger.Logi("You didn't want to play our game :(");
					window.close();
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
				
				if (menu.getPaused())
					menu.setPaused(false);
				else
				{
					menu.setPaused(true);
					logger.Logi("The game was paused");
				}
			}
		}

		window.clear();

		//draw stuff
		if (menu.getIsInMenu()) {

			if (!menu.getStageChooser()) {
				window.draw(menu.getMenuSprite());
				window.draw(menu.getStartText());
				window.draw(menu.getExitText());
			}
			else {
				window.draw(menu.getStageText());
				window.draw(menu.getStageOneText());
				window.draw(menu.getStageTwoText());
				window.draw(menu.getStageThreeText());
				window.draw(menu.getStageFourText());
				//De incarcat stage-urile
			}

		}

		if (menu.getPaused()) {
			window.draw(menu.getPauseText());
		}

		if (!menu.getIsInMenu()) {

			//do movement and draw local player
			doLocalPlayerMovement();
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

			window.draw(m_bullet->m_bulletSprite);
		}

		window.display();
	}
}

bool Engine::moveTank(Tank* tankToMove, const char direction, float speed)
{
	sf::FloatRect intersection;

	switch (direction) {
	case DIR_UP:
		
		tankToMove->m_tankSprite.move(0, -speed);

		if (handleCollision(tankToMove, intersection)) {
			tankToMove->m_tankSprite.move(0, intersection.height);
			return false;
		}

		if (tankToMove->m_tankSprite.getRotation() != 0)
		{
			tankToMove->m_tankSprite.setRotation(0.f);
		}
		
		break;

	case DIR_DOWN:

		tankToMove->m_tankSprite.move(0, speed);

		if (handleCollision(tankToMove, intersection)) {
			tankToMove->m_tankSprite.move(0, -intersection.height);
			return false;
		}

		if (tankToMove->m_tankSprite.getRotation() != 180)
			tankToMove->m_tankSprite.setRotation(180.f);

		break;

	case DIR_LEFT:

		tankToMove->m_tankSprite.move(-speed, 0);

		if (handleCollision(tankToMove, intersection)) {
			tankToMove->m_tankSprite.move(intersection.width, 0);
			return false;
		}

		if (tankToMove->m_tankSprite.getRotation() != -90)
			tankToMove->m_tankSprite.setRotation(-90.f);

		break;

	case DIR_RIGHT:

		tankToMove->m_tankSprite.move(speed, 0);

		if (handleCollision(tankToMove, intersection)) {
			tankToMove->m_tankSprite.move(-intersection.width, 0);
			return false;
		}

		if (tankToMove->m_tankSprite.getRotation() != 90)
			tankToMove->m_tankSprite.setRotation(90.f);

		break;

	}

	// daca s-a executat miscarea, returnam true
	return true;
}

bool Engine::bulletLogic(Bullet* bullet, Tank* tankToShoot, const char direction)
{	
		switch (direction) {
		case DIR_UP:

			bullet->m_bulletSprite.move(0, -15);
			break;

		case DIR_DOWN:

			bullet->m_bulletSprite.move(0, 15);
			break;

		case DIR_LEFT:

			bullet->m_bulletSprite.move(-15 ,0);
			break;

		case DIR_RIGHT:

			bullet->m_bulletSprite.move(15 ,0);
			break;
		}
		return true;
}

bool Engine::handleCollision(Tank* tankToCheck, sf::FloatRect& intersection)
{
	sf::FloatRect firstSpriteBounds = tankToCheck->m_tankSprite.getGlobalBounds();

	for (auto enemyTank : m_enemyTanks) {

		if (tankToCheck == enemyTank)
			continue;

		sf::FloatRect secondSpriteBounds = enemyTank->m_tankSprite.getGlobalBounds();

		if (firstSpriteBounds.intersects(secondSpriteBounds, intersection)) {
			//tankToCheck->m_tankSprite.setPosition(tankToCheck->getLastNonCollidedPosition().first, tankToCheck->getLastNonCollidedPosition().second);
			return true;
		}
	}

	if (tankToCheck != m_localPlayerTank) {
		if (firstSpriteBounds.intersects(m_localPlayerTank->m_tankSprite.getGlobalBounds(), intersection)) {
			return true;
		}
	}

	for (auto entity : m_worldEntities) {

		if (entity->getType() == entityType::Bush)
			continue;

		sf::FloatRect secondSpriteBounds = entity->getSprite().getGlobalBounds();

		if (firstSpriteBounds.intersects(secondSpriteBounds, intersection)) {
			return true;
		}
	}
	
	return false;
}

void Engine::doLocalPlayerMovement()
{
	gameEngine.moveTank(m_localPlayerTank, m_localPlayerTank->getTankDirection(), m_localPlayerTank->getTankSpeed());
}

void Engine::setUpWorld()
{
	unsigned short x = 0;
	unsigned short y = 0;
	float worldEntitySize = 48;

	std::string inputFromFile;
	std::ifstream file("../stages/stage1.txt");

	while (std::getline(file, inputFromFile)) {
		x = 0;
		for (auto chr : inputFromFile) {

			switch (chr) {
				case 'w': {

					m_worldEntities.push_back(new WorldEntity(entityType::WorldBound, x * worldEntitySize + worldEntitySize / 2, y * worldEntitySize + worldEntitySize / 2));
					break;
				}
				case 'b': {
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * worldEntitySize, y * worldEntitySize));
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize));
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize));
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * worldEntitySize, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * worldEntitySize, y * worldEntitySize + worldEntitySize / 3));
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + worldEntitySize / 3));
					m_worldEntities.push_back(new WorldEntity(entityType::Brick, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + worldEntitySize / 3));
					break;
				}
				case 's': {
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * worldEntitySize, y * worldEntitySize));
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize));
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize));
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * worldEntitySize, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * worldEntitySize, y * worldEntitySize + worldEntitySize / 3));
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + worldEntitySize / 3));
					m_worldEntities.push_back(new WorldEntity(entityType::Steel, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + worldEntitySize / 3));					
					break;
				}
				case 'e': {
					m_worldEntities.push_back(new WorldEntity(entityType::Eagle, x * worldEntitySize + worldEntitySize / 2, y * worldEntitySize + worldEntitySize / 2));

					break;
				}
				case ' ': {

					break;
				}
				case 'g': {
					m_worldEntities.push_back(new WorldEntity(entityType::Bush, x * worldEntitySize + worldEntitySize / 2, y * worldEntitySize + worldEntitySize / 2));
					break;
				}
				case 'i': {
					m_worldEntities.push_back(new WorldEntity(entityType::Ice, x * worldEntitySize + worldEntitySize / 2, y * worldEntitySize + worldEntitySize / 2));
					break;
				}
				case 'a': {
					m_worldEntities.push_back(new WorldEntity(entityType::Water, x * worldEntitySize + worldEntitySize / 2, y * worldEntitySize + worldEntitySize / 2));
					break;
				}
				case 'h': {
					m_enemyTanks.push_back(new Enemy(x * worldEntitySize + worldEntitySize / 2, y * worldEntitySize + worldEntitySize / 2));
				}
			}

			x++;
		}
		y++;
	}
}


