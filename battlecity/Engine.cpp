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
	m_localPlayerTankIsMoving = false;
}

Engine::~Engine()
{
}

void Engine::runGame() {

	Menu menu;

	sf::Music menuMusic;

	if (!menuMusic.openFromFile("../resources/menumusic.wav"))
		logger.Logi(Logger::Level::Error,"Nu s-a putut incarca fisierul de muzica.");

	menuMusic.setVolume(0.60f);
	menuMusic.play();

	int savedMenuOption = menu.getMenuOption();

	sf::RenderWindow window(sf::VideoMode(720, 720), "World of Tanks Vaslui");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		if (menu.getIsInMenu()) {
			menu.updateMenuColor();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

			if(!menu.getIsInMenu()) {
				m_localPlayerTank->setTankDirection(DIR_UP);
				logger.Logi(Logger::Level::Debug,"The player is moving upwards");
				m_localPlayerTankIsMoving = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

			if (!menu.getIsInMenu()) {
				m_localPlayerTank->setTankDirection(DIR_DOWN);
				logger.Logi(Logger::Level::Debug,"The player moved downwards");
				m_localPlayerTankIsMoving = true;
			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

			if (!menu.getIsInMenu()) {
				m_localPlayerTank->setTankDirection(DIR_LEFT);
				logger.Logi(Logger::Level::Debug,"The player moved to the left");
				m_localPlayerTankIsMoving = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

			if (!menu.getIsInMenu()) {
				m_localPlayerTank->setTankDirection(DIR_RIGHT);
				logger.Logi(Logger::Level::Debug,"The player moved to the right");
				m_localPlayerTankIsMoving = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			logger.Logi(Logger::Level::Info,"Game closed");
			window.close();
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				logger.Logi(Logger::Level::Info,"See you later");
				window.close();
			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
			{
				if (menu.getIsInMenu()) {
					savedMenuOption = menu.getMenuOption();
					savedMenuOption--;
					savedMenuOption = std::clamp(savedMenuOption, 0, menu.getStageChooser() ? 3 : 1);
					menu.setMenuOption(savedMenuOption);
				}
				else
				{
					m_localPlayerTankIsMoving = false;
				}
			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
			{
				if (menu.getIsInMenu()) {
					savedMenuOption = menu.getMenuOption();
					savedMenuOption++;
					savedMenuOption = std::clamp(savedMenuOption, 0, menu.getStageChooser() ? 3 : 1);
					menu.setMenuOption(savedMenuOption);
				}
				else
				{
					m_localPlayerTankIsMoving = false;
				}
			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left)
			{
				m_localPlayerTankIsMoving = false;
			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right)
			{
				m_localPlayerTankIsMoving = false;
			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) {

				if (menu.getIsInMenu() && menu.getMenuOption() == 0 && !menu.getStageChooser())
					menu.setStageChooser(true);
				else if (menu.getStageChooser() && menu.getIsInMenu()) {
					setUpWorld(menu.getMenuOption());
					menu.setStageChooser(false);
					menu.setIsInMenu(false);
				}
				else if (menu.getIsInMenu() && !menu.getStageChooser() && menu.getMenuOption() == 1) {
					logger.Logi(Logger::Level::Error, "Really, you don't want to play our game? :'(");
					window.close();
				}


			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P) {
				
				menu.getPaused() ? menu.setPaused(false) : menu.setPaused(true);
				if (menu.getPaused() == false)
					logger.Logi(Logger::Level::Info, "Game resumed");
				else
					logger.Logi(Logger::Level::Info, "Game paused");
			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {

				if (menu.getIsInMenu())
					continue;

				if (tankAlreadyFired(m_localPlayerTank))
					continue;

				logger.Logi(Logger::Level::Debug, "Fire");
				auto tempDirection = m_localPlayerTank->getTankDirection();
				auto tempPos = m_localPlayerTank->m_tankSprite.getPosition();
				
				switch (tempDirection) {
					case DIR_UP: m_bulletVec.push_back(std::make_unique<Bullet>(std::make_pair(tempPos.x, tempPos.y - 6), tempDirection, m_localPlayerTank)); break;
					case DIR_DOWN: m_bulletVec.push_back(std::make_unique<Bullet>(std::make_pair(tempPos.x, tempPos.y + 6), tempDirection, m_localPlayerTank)); break;
					case DIR_LEFT: m_bulletVec.push_back(std::make_unique<Bullet>(std::make_pair(tempPos.x - 6, tempPos.y), tempDirection, m_localPlayerTank)); break;
					case DIR_RIGHT: m_bulletVec.push_back(std::make_unique<Bullet>(std::make_pair(tempPos.x + 6, tempPos.y), tempDirection, m_localPlayerTank)); break;
				}
			}

		}

		window.clear();

		//draw stuff
		if (menu.getIsInMenu() && !menu.getStageChooser()) {
			window.draw(menu.getMenuSprite());
			window.draw(menu.getStartText());
			window.draw(menu.getExitText());
		}
		else if (menu.getStageChooser()) {
			window.draw(menu.getStageText());
			window.draw(menu.getStageOneText());
			window.draw(menu.getStageTwoText());
			window.draw(menu.getStageThreeText());
			window.draw(menu.getStageFourText());
		}
		else if (menu.getPaused()) {
			window.draw(menu.getPauseText());
		}
		else if (!menu.getIsInMenu()) {

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

			//bullet logic and draw bullets
			for (auto& bullets : m_bulletVec) {

				if (!bullets.get()->handleBullet(m_bulletVec, m_worldEntities, m_enemyTanks, m_localPlayerTank))
					break;

				window.draw(bullets.get()->m_bulletSprite);
			}
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
			tankToMove->m_tankSprite.setRotation(0.f);
		
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

bool Engine::tankAlreadyFired(Tank* tankToCheck)
{
	for (auto& bullet : m_bulletVec) {
		if (bullet->getFiredBy() == tankToCheck) {
			return true;
		}
	}

	return false;
}

bool Engine::handleCollision(Tank* tankToCheck, sf::FloatRect& intersection)
{
	sf::FloatRect firstSpriteBounds = tankToCheck->m_tankSprite.getGlobalBounds();

	for (auto enemyTank : m_enemyTanks) {

		if (tankToCheck == enemyTank)
			continue;

		sf::FloatRect secondSpriteBounds = enemyTank->m_tankSprite.getGlobalBounds();

		if (firstSpriteBounds.intersects(secondSpriteBounds, intersection)) {
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
		if (entity->getType() == entityType::Ice)
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
	if (m_localPlayerTankIsMoving)
		gameEngine.moveTank(m_localPlayerTank, m_localPlayerTank->getTankDirection(), m_localPlayerTank->getTankSpeed());
}

void Engine::setUpWorld(unsigned short stage)
{
	logger.Logi(Logger::Level::Info, "Game Started");
	unsigned short x = 0;
	unsigned short y = 0;
	float worldEntitySize = 48;
	std::vector<std::string> fileNames = { "../stages/stage1.txt", "../stages/stage2.txt", "../stages/stage3.txt", "../stages/stage4.txt" };
	std::string inputFromFile;
	std::ifstream file(fileNames.at(stage));

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
					m_worldEntities.push_back(new WorldEntity(entityType::Bush, x * worldEntitySize, y * worldEntitySize));
					m_worldEntities.push_back(new WorldEntity(entityType::Bush, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize));
					m_worldEntities.push_back(new WorldEntity(entityType::Bush, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize));
					m_worldEntities.push_back(new WorldEntity(entityType::Bush, x * worldEntitySize, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Bush, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Bush, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Bush, x * worldEntitySize, y * worldEntitySize + worldEntitySize / 3));
					m_worldEntities.push_back(new WorldEntity(entityType::Bush, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + worldEntitySize / 3));
					m_worldEntities.push_back(new WorldEntity(entityType::Bush, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + worldEntitySize / 3));
					break;
				}
				case 'i': {
					m_worldEntities.push_back(new WorldEntity(entityType::Ice, x * worldEntitySize, y * worldEntitySize));
					m_worldEntities.push_back(new WorldEntity(entityType::Ice, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize));
					m_worldEntities.push_back(new WorldEntity(entityType::Ice, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize));
					m_worldEntities.push_back(new WorldEntity(entityType::Ice, x * worldEntitySize, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Ice, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Ice, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Ice, x * worldEntitySize, y * worldEntitySize + worldEntitySize / 3));
					m_worldEntities.push_back(new WorldEntity(entityType::Ice, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + worldEntitySize / 3));
					m_worldEntities.push_back(new WorldEntity(entityType::Ice, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + worldEntitySize / 3));
					break;
				}
				case 'a': {
					m_worldEntities.push_back(new WorldEntity(entityType::Water, x * worldEntitySize, y * worldEntitySize));
					m_worldEntities.push_back(new WorldEntity(entityType::Water, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize));
					m_worldEntities.push_back(new WorldEntity(entityType::Water, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize));
					m_worldEntities.push_back(new WorldEntity(entityType::Water, x * worldEntitySize, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Water, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Water, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(new WorldEntity(entityType::Water, x * worldEntitySize, y * worldEntitySize + worldEntitySize / 3));
					m_worldEntities.push_back(new WorldEntity(entityType::Water, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + worldEntitySize / 3));
					m_worldEntities.push_back(new WorldEntity(entityType::Water, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + worldEntitySize / 3));
					break;
				}
				case 'h': {
					m_enemyTanks.push_back(new Enemy(x * worldEntitySize + worldEntitySize / 2, y * worldEntitySize + worldEntitySize / 2));
					break;
				}
				case 'p': {
					m_localPlayerTank = new Tank(x * worldEntitySize + worldEntitySize / 2, y * worldEntitySize + worldEntitySize / 2);
				}
			}

			x++;
		}
		y++;
	}
	logger.Logi(Logger::Level::Info, m_worldEntities.size(), " elements were loaded in this stage ");
}


