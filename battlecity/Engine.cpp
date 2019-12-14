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
std::ofstream logFile("log.log", std::ios::app);
Logger logger(std::cout, Logger::Level::Info);

void Engine::runGame() {
	Menu menu;
	int savedMenuOption = menu.getMenuOption();
	sf::Sprite menuSprite = menu.createSprite();
	sf::Font menuFont = menu.getMenuFont();
	sf::Text startText("Start", menuFont);
	sf::Text exitText("Exit", menuFont);
	sf::Text pauseText("Paused", menuFont);
	sf::Text stageText("Choose your stage \n(use arrow keys)", menuFont);
	sf::Text stageOne("Stage 1", menuFont);
	sf::Text stageTwo("Stage 2", menuFont);
	sf::Text stageThree("Stage 3", menuFont);
	sf::Text stageFour("Stage 4", menuFont);

	sf::Music menuMusic;

	if (!menuMusic.openFromFile("../resources/menumusic.wav"))
	{
		std::cout << "Nu s-a putut incarca fisierul de muzica.";
	}

	menuMusic.setVolume(0.60f);
	menuMusic.play();

	startText.setPosition(287, 310);
	exitText.setPosition(302, 380);
	pauseText.setPosition(270, 360);
	stageText.setCharacterSize(25.f);
	stageText.setPosition(50, 150);
	stageOne.setCharacterSize(20.f);
	stageOne.setPosition(200, 250);
	stageTwo.setCharacterSize(20.f);
	stageTwo.setPosition(200, 300);
	stageThree.setCharacterSize(20.f);
	stageThree.setPosition(200, 350);
	stageFour.setCharacterSize(20.f);
	stageFour.setPosition(200, 400);

	sf::RenderWindow window(sf::VideoMode(720, 720), "World of Tanks Vaslui");
	window.setFramerateLimit(60);
	setUpWorld();

	while (window.isOpen())
	{
		if (menu.getIsInMenu()) {
			startText.setFillColor(menu.getMenuOption() ? sf::Color::White : sf::Color::Yellow);
			exitText.setFillColor(menu.getMenuOption() ? sf::Color::Yellow : sf::Color::White);
			stageOne.setFillColor(menu.getMenuOption() == 0 ? sf::Color::Yellow : sf::Color::White);
			stageTwo.setFillColor(menu.getMenuOption() == 1 ? sf::Color::Yellow : sf::Color::White);
			stageThree.setFillColor(menu.getMenuOption() == 2 ? sf::Color::Yellow : sf::Color::White);
			stageFour.setFillColor(menu.getMenuOption() == 3 ? sf::Color::Yellow : sf::Color::White);

		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (menu.getIsInMenu())

				switch (event.type)
				{
				case sf::Event::Closed: {
					window.close();
					break;
				}
				case sf::Event::KeyReleased: {

					switch (event.key.code) {

					case sf::Keyboard::Up:
						
							savedMenuOption = menu.getMenuOption();
						savedMenuOption--;
						savedMenuOption = std::clamp(savedMenuOption, 0, 1);
						
							menu.setMenuOption(savedMenuOption);
						std::cout << menu.getMenuOption();
						break;
						
					case sf::Keyboard::Down:
						
							savedMenuOption = menu.getMenuOption();
						savedMenuOption++;
						savedMenuOption = std::clamp(savedMenuOption, 0, 1);
						
							menu.setMenuOption(savedMenuOption);
						std::cout << menu.getMenuOption();
						break;
						
					case sf::Keyboard::Enter:
						
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
						break;

					}
				}
				}
			else
				if (event.type == sf::Event::Closed)
				{
					window.close();
					logger.Logi("The game was closed");
				}
				{

				float tankSpeed = 10.0f;

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
						moveTank(m_localPlayerTank, DIR_UP, tankSpeed);
						logger.Logi("The player moved upwards");
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						moveTank(m_localPlayerTank, DIR_DOWN, tankSpeed);
						logger.Logi("The player moved downwards");
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
						moveTank(m_localPlayerTank, DIR_LEFT, tankSpeed);
						logger.Logi("The player moved to the left");
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
						moveTank(m_localPlayerTank, DIR_RIGHT, tankSpeed);
						logger.Logi("The player moved to the right");
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
						if (menu.getPaused())
							menu.setPaused(false);
						else
						{
							menu.setPaused(true);
							logger.Logi("The game was paused");
						}
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
					{
						window.close();
						logger.Logi("Gata pe azi?");
					}
				}
		}

		window.clear();

		//draw stuff
		if (menu.getIsInMenu())
		{
			if (!menu.getStageChooser()) {
				window.draw(menuSprite);
				window.draw(startText);
				window.draw(exitText);
			}
			else
			{
				window.draw(stageText);
				window.draw(stageOne);
				window.draw(stageTwo);
				window.draw(stageThree);
				window.draw(stageFour);
				//De incarcat stage-urile
			}

		}
		else
		if (menu.getPaused()) {
			window.draw(pauseText);
			}
		else
		{
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

			
		}
		window.display();
	}
}

bool Engine::moveTank(Tank* tankToMove, const char direction, float speed)
{

	switch (direction) {
	case DIR_UP:
		
		if (handleCollision(tankToMove))
			return false;

		tankToMove->m_tankSprite.move(0, -speed);

		if (tankToMove->m_tankSprite.getRotation() != 0)
		{
			tankToMove->m_tankSprite.setRotation(0.f);
		}
		
		break;

	case DIR_DOWN:

		if (handleCollision(tankToMove))
			return false;

		tankToMove->m_tankSprite.move(0, speed);

		if (tankToMove->m_tankSprite.getRotation() != 180)
			tankToMove->m_tankSprite.setRotation(180.f);

		break;

	case DIR_LEFT:

		if (handleCollision(tankToMove))
			return false;

		tankToMove->m_tankSprite.move(-speed, 0);

		if (tankToMove->m_tankSprite.getRotation() != -90)
			tankToMove->m_tankSprite.setRotation(-90.f);

		break;

	case DIR_RIGHT:

		if (handleCollision(tankToMove))
			return false;

		tankToMove->m_tankSprite.move(speed, 0);

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
