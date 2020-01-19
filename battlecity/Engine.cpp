#include "Engine.h"
#include "Tank.h"
#include "Macros.h"
#include <fstream>

std::ofstream logFile("log.log", std::ios::app);
Logger logger(std::cout, Logger::Level::Info);

Engine::Engine()
{
	if (!tankMovingBuffer.loadFromFile("../resources/tankMoving.wav"))
		logger.Logi(Logger::Level::Error, "Nu s-a putut incarca fisierul de muzica.");

	if (!bulletBuffer.loadFromFile("../resources/bulletSound.wav"))
		logger.Logi(Logger::Level::Error, "Nu s-a putut incarca fisierul de muzica.");

	if (!tankIdleBuffer.loadFromFile("../resources/tankIdle.wav"))
		logger.Logi(Logger::Level::Error, "Nu s-a putut incarca fisierul de muzica.");

	if (!gameOverBuffer.loadFromFile("../resources/gameOver.wav"))
		logger.Logi(Logger::Level::Error, "Nu s-a putut incarca fisierul de muzica.");

	if (!wallHitSoundBuffer.loadFromFile("../resources/wallHit.wav"))
		logger.Logi(Logger::Level::Error, "Nu s-a putut incarca fisierul de muzica.");

	if (!tankHitSoundBuffer.loadFromFile("../resources/tankHit.wav"))
		logger.Logi(Logger::Level::Error, "Nu s-a putut incarca fisierul de muzica.");

	if (!solidHitSoundBuffer.loadFromFile("../resources/solidHit.wav"))
		logger.Logi(Logger::Level::Error, "Nu s-a putut incarca fisierul de muzica.");

	m_enemyLifeTexture.loadFromFile("../resources/enemyLife.png");
	m_explosionTextureSheet.loadFromFile("../resources/explosion.png");
	m_spawnAnimTextureSheet.loadFromFile("../resources/spawnAnim.png");

	tankHitSound.setBuffer(tankHitSoundBuffer);
	tankHitSound.setVolume(20.5f);

	solidHitSound.setBuffer(solidHitSoundBuffer);
	solidHitSound.setVolume(10.5f);

	explosionAnim = createExplosionAnimation();
	spawnAnim = createSpawnAnimation();

	wallHitSound.setBuffer(wallHitSoundBuffer);
	wallHitSound.setVolume(20.5f);

	tankMoving.setBuffer(tankMovingBuffer);
	tankMoving.setVolume(15.5f);

	gameOver.setBuffer(gameOverBuffer);
	gameOver.setVolume(25.5f);

	bulletSound.setBuffer(bulletBuffer);
	bulletSound.setVolume(15.5f);

	tankIdle.setBuffer(tankIdleBuffer);
	tankIdle.setVolume(15.5f);

	onStageStartPresets();
	setUpPUSpawnPoints();
}

Engine::~Engine()
{
}

void Engine::runGame() {

	Menu menu;
	sf::RectangleShape rightSideBg(sf::Vector2f(180, 720));
	rightSideBg.setFillColor(sf::Color(127, 127, 127, 255));
	rightSideBg.setPosition(sf::Vector2f(720, 0));

	sf::Music menuMusic;

	if (!menuMusic.openFromFile("../resources/menumusic.wav"))
		logger.Logi(Logger::Level::Error,"Nu s-a putut incarca fisierul de muzica.");

	menuMusic.setVolume(25.5f);
	menuMusic.play();

	int savedMenuOption = menu.getMenuOption();

	sf::RenderWindow window(sf::VideoMode(900, 720), "Battle City");
	window.setFramerateLimit(60);
	sf::Clock clock;
	sf::Clock enemyClock;
	sf::Clock animClock;

	while (window.isOpen())
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

			if(!menu.getIsInMenu()) {
				m_localPlayerTank->setTankDirection(DIR_UP);
				logger.Logi(Logger::Level::Debug,"The player is moving upwards");
				m_localPlayerTankIsMoving = true;
				tankIdle.stop();

				if (tankMoving.getStatus() != sf::Sound::Playing)
					tankMoving.play();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

			if (!menu.getIsInMenu()) {
				m_localPlayerTank->setTankDirection(DIR_DOWN);
				logger.Logi(Logger::Level::Debug,"The player moved downwards");
				m_localPlayerTankIsMoving = true;
				tankIdle.stop();

				if (tankMoving.getStatus() != sf::Sound::Playing)
					tankMoving.play();
			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

			if (!menu.getIsInMenu()) {
				m_localPlayerTank->setTankDirection(DIR_LEFT);
				logger.Logi(Logger::Level::Debug,"The player moved to the left");
				m_localPlayerTankIsMoving = true;
				tankIdle.stop();

				if (tankMoving.getStatus() != sf::Sound::Playing)
					tankMoving.play();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

			if (!menu.getIsInMenu()) {
				m_localPlayerTank->setTankDirection(DIR_RIGHT);
				logger.Logi(Logger::Level::Debug,"The player moved to the right");
				m_localPlayerTankIsMoving = true;
				tankIdle.stop();

				if (tankMoving.getStatus() != sf::Sound::Playing)
					tankMoving.play();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			logger.Logi(Logger::Level::Info,"Game closed");
			window.close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			logger.Logi(Logger::Level::Info, "Level skipped, cheater!");
			advanceStageSetup();
			onStageStartPresets();
			m_nextStageScene = true;
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				logger.Logi(Logger::Level::Info,"See you later");
				resetGameLogic();
				window.close();
			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
			{
				if (menu.getIsInMenu()) {
					savedMenuOption = menu.getMenuOption();
					savedMenuOption--;
					savedMenuOption = std::clamp(savedMenuOption, 0, menu.getStageChooser() ? 3 : 2);
					menu.setMenuOption(savedMenuOption);
				}
				else
				{
					m_localPlayerTankIsMoving = false;
					tankMoving.stop();
					tankIdle.setLoop(true);
					tankIdle.play();
				}
			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
			{
				if (menu.getIsInMenu()) {
					savedMenuOption = menu.getMenuOption();
					savedMenuOption++;
					savedMenuOption = std::clamp(savedMenuOption, 0, menu.getStageChooser() ? 3 : 2);
					menu.setMenuOption(savedMenuOption);
				}
				else
				{
					m_localPlayerTankIsMoving = false;
					tankMoving.stop();
					tankIdle.setLoop(true);
					tankIdle.play();
				}
			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left)
			{
				if (!menu.getIsInMenu()) {
					m_localPlayerTankIsMoving = false;
					tankMoving.stop();
					tankIdle.setLoop(true);
					tankIdle.play();
				}
			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right)
			{
				if (!menu.getIsInMenu()) {
					m_localPlayerTankIsMoving = false;
					tankMoving.stop();
					tankIdle.setLoop(true);
					tankIdle.play();
				}
			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) {

				if (menu.getIsInMenu() && menu.getMenuOption() == 0) {

					resetGameLogic();
					onStageStartPresets();
					setUpWorld(0);
					tankIdle.play();
					menu.setIsInMenu(false);
				}
				else if (menu.getIsInMenu() && menu.getMenuOption() == 2) {
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

				if (tankAlreadyFired(m_localPlayerTank.get()) > 0 && m_starsCollected == 0)
					continue;

				if (tankAlreadyFired(m_localPlayerTank.get()) > 2 && m_starsCollected >= 2)
					continue;

				if ((m_localPlayerTank->m_tankSprite.getPosition().x > 900 ||
					m_localPlayerTank->m_tankSprite.getPosition().x < 0) ||
					(m_localPlayerTank->m_tankSprite.getPosition().y > 720 ||
					m_localPlayerTank->m_tankSprite.getPosition().y < 0))
					continue;

				logger.Logi(Logger::Level::Debug, "Fire");
				auto tempDirection = m_localPlayerTank->getTankDirection();
				auto tempPos = m_localPlayerTank->m_tankSprite.getPosition();
				
				switch (tempDirection) {
					case DIR_UP: m_bulletVec.push_back(std::make_unique<Bullet>(std::make_pair(tempPos.x, tempPos.y - 6), tempDirection, m_localPlayerTank.get(), false)); break;
					case DIR_DOWN: m_bulletVec.push_back(std::make_unique<Bullet>(std::make_pair(tempPos.x, tempPos.y + 6), tempDirection, m_localPlayerTank.get(), false)); break;
					case DIR_LEFT: m_bulletVec.push_back(std::make_unique<Bullet>(std::make_pair(tempPos.x - 6, tempPos.y), tempDirection, m_localPlayerTank.get(), false)); break;
					case DIR_RIGHT: m_bulletVec.push_back(std::make_unique<Bullet>(std::make_pair(tempPos.x + 6, tempPos.y), tempDirection, m_localPlayerTank.get(), false)); break;
				}

				bulletSound.play();
			}

		}

		//advance to the next stage if player has killed 20 enemy tanks
		if (m_localPlayerKills == 20) {
			advanceStageSetup();
			onStageStartPresets();
			m_nextStageScene = true;
			menuMusic.play();
		}

		window.clear();

		//draw stuff

		if (menu.getIsInMenu()) {
			menu.updateSprites();
			window.draw(menu.getMenuSprite());
			window.draw(menu.getTankSprite());
			window.draw(menu.getOnePlayerText());
			window.draw(menu.getTwoPlayersText());
			window.draw(menu.getExitText());
		}
		else if (menu.getPaused()) {
			window.draw(menu.getPauseText());
		}
		else if (m_gameOver)
		{
			menu.scoreDisplay.setString("You score is: " + std::to_string(m_localPlayerScore));
			window.draw(menu.m_gameOverSprite);
			window.draw(menu.scoreDisplay);
			tankIdle.stop();
			tankMoving.stop();

			if (menu.m_gameOverSprite.getPosition().y != 200) {
				menu.m_gameOverSprite.move(0, 1);
			}
			else {
				resetGameLogic();
				menu.m_gameOverSprite.setPosition(300, 0);
				menu.setIsInMenu(true);
			}

			if (gameOver.getStatus() != sf::Sound::Playing && m_playedMusic == false)
			{
				gameOver.play();
				m_playedMusic = true;
			}
			
		}
		else if (m_nextStageScene) {
			menu.drawStageChangeScene(window, m_currentStage, clock, m_nextStageScene);
			float secondCounter = 0.f;
			tankMoving.stop();
			bulletSound.stop();	
		}
		else if (!menu.getIsInMenu()) {

			clock.restart();
			sf::Time frameTime = animClock.restart();
			sf::Time elapsed = enemyClock.restart();


			// powerUps
			{
				//grenade
				if (m_activePowerUps.at(0)) {
					m_enemyTanks.clear();
					logger.Logi(Logger::Level::Info, "All enemies disappeared");
					m_activePowerUps.at(0) = false;
				}
				
				// tank - extra life
				if (m_activePowerUps.at(5)) {
					m_localPlayerLives[0]++;
					m_localPlayerLives[1]++;
					logger.Logi(Logger::Level::Info, "You received an extra life");
					m_activePowerUps.at(5) = false;
				}

				// shield
				if (m_activePowerUps.at(2)) {
					m_secondsElapsed += frameTime.asSeconds();

					if (m_secondsElapsed >= 10) {
						m_secondsElapsed = 0;
						m_activePowerUps.at(2) = false;
						logger.Logi(Logger::Level::Info, "You are no longer immune!");
					}
					
				}

				
			}

			//draw ice first - tank should be over ice so we have to draw ice first
			for (auto& entity : m_iceVec) {
				window.draw(entity->getSprite());
			}

			//do movement and draw local player
			doLocalPlayerMovement();
			window.draw(m_localPlayerTank->m_tankSprite);
			std::cout << m_starsCollected << "\n";

			//do movement and draw enemies
			for (auto &enemyTank : m_enemyTanks) {
			
				// timer power up, enemies should freeze
				if (m_activePowerUps.at(1)) {
					m_secondsElapsed += frameTime.asSeconds();
					if (m_secondsElapsed >= 10)
					{
						m_secondsElapsed = 0;
						m_activePowerUps.at(1) = false;
						logger.Logi(Logger::Level::Info, "Your power up expired, enemies are no longer frozen");
					}
				}
				else {
					enemyTank->doMovement();
				}

				if (tankAlreadyFired(enemyTank.get()) == 0 && !m_activePowerUps.at(1)) {
					enemyTank->fireBullet(m_bulletVec, elapsed);
				}

				window.draw(enemyTank->m_tankSprite);
			}

			//draw world entities
			for (auto &entity : m_worldEntities) {
				window.draw(entity->getSprite());
			}

			//bullet logic and draw bullets
			for (auto& bullets : m_bulletVec) {

				if (!bullets.get()->handleBullet(m_bulletVec, m_worldEntities, m_enemyTanks, m_powerUps, m_powerUpSpawnPoints, m_wallHit, m_tankHit, m_solidHit))
				{
					break;
				}
				if (m_wallHit == true)
				{
					wallHitSound.play();
					m_wallHit = false;
				}
				if (m_solidHit == true)
				{
					solidHitSound.play();
					m_solidHit = false;
				}
				if (m_tankHit == true)
				{
					tankHitSound.play();
					m_tankHit = false;
				}
				window.draw(bullets.get()->m_bulletSprite);
			}

			for (auto& explosion : explosionsVec) {
				explosion.update(frameTime);
				window.draw(explosion);
			}

			explosionsVec.erase(std::remove_if(explosionsVec.begin(), explosionsVec.end(), [](AnimatedSprite sprite) { return sprite.isPlaying() == false; }), explosionsVec.end());

			//draw bush - bullet should be under bush so we have to draw bush first
			for (auto& entity : m_bushVec) {
				window.draw(entity->getSprite());
			}

			//we should always have 3 enemies on the map
			if (m_enemyTanks.size() + spawnAnimVec.size() < 3) {

				auto generatedPos = m_enemySpawnPoints.at(rand() % m_enemySpawnPoints.size());
				bool okToSpawn = false;

				/*sf::RectangleShape dummy;
				dummy.setSize(sf::Vector2f(27, 30));
				dummy.setPosition(generatedPos.first, generatedPos.second);

				for (auto& enemy : m_enemyTanks) {
					if (!dummy.getGlobalBounds().intersects(enemy->m_tankSprite.getGlobalBounds()))
						okToSpawn = true;
				}

				if (okToSpawn) {*/
				AnimatedSprite spawn(sf::seconds(0.25), true, false);
				spawn.setPosition(generatedPos.first, generatedPos.second);
				spawn.setOrigin(sf::Vector2f(16.5, 15.5));
				spawn.play(spawnAnim);
				spawnAnimVec.push_back(spawn);

				if (!enemyLifeSprites.empty())
					enemyLifeSprites.pop_back();
				//}

			}

			for (auto& spawnAnim : spawnAnimVec) {

				spawnAnim.update(frameTime);
				window.draw(spawnAnim);

				if (!spawnAnim.isPlaying()) {
					m_enemiesRespawned++;

					if (m_enemiesRespawned == 1 || m_enemiesRespawned == 8 || m_enemiesRespawned == 15) {
						m_enemyTanks.push_back(std::make_unique<Enemy>(spawnAnim.getPosition().x, spawnAnim.getPosition().y, true));
					}
					else
					{
						m_enemyTanks.push_back(std::make_unique<Enemy>(spawnAnim.getPosition().x, spawnAnim.getPosition().y, false));
					}
								
				}

			}

			spawnAnimVec.erase(std::remove_if(spawnAnimVec.begin(), spawnAnimVec.end(), [](AnimatedSprite sprite) { return sprite.isPlaying() == false; }), spawnAnimVec.end());

			for (auto& powerUp : m_powerUps) {
				window.draw(powerUp.getSprite());
			}

			if (m_localPlayerSpawnSprite != nullptr) {
				m_localPlayerSpawnSprite->update(frameTime);
				window.draw(*m_localPlayerSpawnSprite);

				if (!m_localPlayerSpawnSprite->isPlaying()) {
					m_localPlayerTank->m_tankSprite.setPosition(gameEngine.m_localPlayerSpawnPoint.first, gameEngine.m_localPlayerSpawnPoint.second);
					delete m_localPlayerSpawnSprite;
					m_localPlayerSpawnSprite = nullptr;
				}
			}

			window.draw(rightSideBg);

			for (auto enemyLife : enemyLifeSprites) {
				window.draw(enemyLife);
			}

			window.draw(menu.getStageFlag());
			window.draw(menu.getCurrentStageText());
			window.draw(menu.getFirstPlayerText());
			menu.setFirstPlayerLivesText(m_localPlayerLives[0]);
			window.draw(menu.getFirstPlayerLivesText());

		}
		
		window.display();
	}
}

bool Engine::moveTank(Tank* tankToMove, const char direction, float speed)
{
	sf::FloatRect intersection;
	
	switch (direction) {
	case DIR_UP:

		if (tankToMove->m_tankSprite.getRotation() != 0)
			tankToMove->m_tankSprite.setRotation(0.f);

		if (handleCollision(tankToMove, tankToMove->getTankDirection()))
			tankToMove->m_tankSprite.move(0, -speed);
		else
			return false;

		break;

	case DIR_DOWN:

		if (tankToMove->m_tankSprite.getRotation() != 180)
			tankToMove->m_tankSprite.setRotation(180.f);

		if (handleCollision(tankToMove, tankToMove->getTankDirection()))
			tankToMove->m_tankSprite.move(0, speed);
		else
			return false;
		
		break;

	case DIR_LEFT:

		if (tankToMove->m_tankSprite.getRotation() != -90)
			tankToMove->m_tankSprite.setRotation(-90.f);

		if (handleCollision(tankToMove, tankToMove->getTankDirection()))
			tankToMove->m_tankSprite.move(-speed, 0);
		else
			return false;

		break;

	case DIR_RIGHT:

		if (tankToMove->m_tankSprite.getRotation() != 90)
			tankToMove->m_tankSprite.setRotation(90.f);

		if (handleCollision(tankToMove, tankToMove->getTankDirection()))
			tankToMove->m_tankSprite.move(speed, 0);
		else
			return false;

		break;
	}

	// daca s-a executat miscarea, returnam true
	return true;
}

unsigned short Engine::tankAlreadyFired(Tank* tankToCheck)
{
	unsigned short numberOfBullets = 0;

	for (auto& bullet : m_bulletVec) {
		if (bullet->getFiredBy() == tankToCheck) {
			numberOfBullets++;
		}
	}

	return numberOfBullets;
}

bool Engine::handleCollision(Tank* tankToCheck, char direction)
{
	auto dummySprite = tankToCheck->m_tankSprite;
	auto futurePosition = tankToCheck->m_tankSprite.getPosition();

	switch (direction) {
	case DIR_UP: futurePosition.y -= tankToCheck->getTankSpeed(); break;
	case DIR_DOWN: futurePosition.y += tankToCheck->getTankSpeed(); break;
	case DIR_LEFT: futurePosition.x -= tankToCheck->getTankSpeed(); break;
	case DIR_RIGHT: futurePosition.x += tankToCheck->getTankSpeed(); break;
	}
	
	dummySprite.setPosition(futurePosition);

	sf::FloatRect bounds = dummySprite.getGlobalBounds();

	for (auto& entity : m_worldEntities) {

		if (entity->getType() == entityType::Bush)
			continue;
		if (entity->getType() == entityType::Ice)
			continue;

		sf::FloatRect secondSpriteBounds = entity->getSprite().getGlobalBounds();

		if (bounds.intersects(secondSpriteBounds)) {
			return false;
		}
	}

	for (auto& enemyTank : m_enemyTanks) {

		if (tankToCheck == enemyTank.get())
			continue;

		sf::FloatRect secondSpriteBounds = enemyTank->m_tankSprite.getGlobalBounds();

		if (bounds.intersects(secondSpriteBounds)) {
			return false;
		}
	}

	//for (auto& spawnAnimation : spawnAnimVec) {
	//	sf::FloatRect secondSpriteBounds = spawnAnimation.getGlobalBounds();

	//	if (bounds.intersects(secondSpriteBounds)) {
	//		return false;
	//	}
	//}

	if (tankToCheck == m_localPlayerTank.get()) {
		std::vector<PowerUps>::iterator it;
		for (it = m_powerUps.begin(); it < m_powerUps.end(); it++) {
		
			sf::FloatRect secondSpriteBounds = it->getSprite().getGlobalBounds();

			if (bounds.intersects(secondSpriteBounds)) {
				auto type = it->getType();
				logger.Logi(Logger::Level::Info, "You picked up a power up [", type, "]");

				if (it->getType() == powerUp::StarPU)
					m_starsCollected++;

				m_activePowerUps.at(type) = true;
				m_powerUps.erase(it);
				break;
			}
		}
	}

	if (tankToCheck != m_localPlayerTank.get()) {
		if (bounds.intersects(m_localPlayerTank->m_tankSprite.getGlobalBounds())) {
			return false;
		}
	}

	return true;
}

void Engine::doLocalPlayerMovement()
{
	if (m_localPlayerTankIsMoving) 
	{
		gameEngine.moveTank(m_localPlayerTank.get(), m_localPlayerTank->getTankDirection(), m_localPlayerTank->getTankSpeed());
	}
}

void Engine::setlocalPlayerKills(const unsigned int localPlayerKills)
{
	m_localPlayerKills = localPlayerKills;
}

unsigned int Engine::getLocalPlayerKills() const
{
	return m_localPlayerKills;
}

void Engine::setLocalPlayerScore(const uint64_t localPlayerScore)
{
	m_localPlayerScore = localPlayerScore;
}

uint64_t Engine::getLocalPlayerScore() const
{
	return m_localPlayerScore;
}

void Engine::onStageStartPresets()
{
	unsigned short x = 630;
	unsigned short y = 20;

	enemyLifeSprites.clear();

	for (int i = 0; i < 20; i++) {
		sf::Sprite enemyLifeSprite;
		enemyLifeSprite.setTexture(m_enemyLifeTexture);
		if (i % 2 == 0) {
			x = 730;
			y += 30;
		}
		else {
			x = 760;
		}
			
		enemyLifeSprite.setPosition(x, y);
		enemyLifeSprites.push_back(enemyLifeSprite);
	}

	m_gameOver = false;
	m_localPlayerKills = 0;
	m_localPlayerTankIsMoving = false;
	m_playedMusic = false;
}

void Engine::advanceStageSetup()
{
	m_currentStage += 1;
	if (m_currentStage == 10 || m_currentStage == 20 || m_currentStage == 30)
	{
		m_localPlayerLives[0]++;
		logger.Logi(Logger::Level::Info, "Felicitari ai primit o viata in plus");
	}
	m_worldEntities.clear();
	m_bushVec.clear();
	m_iceVec.clear();
	m_enemyTanks.clear();
	m_bulletVec.clear();

	tankIdle.play();
	tankMoving.stop();
	bulletSound.stop();
	m_gameOver = false;
	m_localPlayerKills = 0;

	setUpWorld(m_currentStage);
}

void Engine::resetGameLogic()
{
	m_currentStage = 0;
	m_worldEntities.clear();
	m_bushVec.clear();
	m_iceVec.clear();
	m_enemyTanks.clear();
	m_bulletVec.clear();
	m_gameOver = false;
	m_localPlayerKills = 0;
	m_localPlayerTankIsMoving = false;
	m_localPlayerLives[0] = 2;
	m_playedMusic = false;
	m_localPlayerScore = 0;
	m_enemiesRespawned = 0;
	explosionsVec.clear();
	spawnAnimVec.clear();

	tankIdle.stop();
	tankMoving.stop();
	bulletSound.stop();
}

void Engine::setUpPUSpawnPoints()
{
	m_powerUpSpawnPoints.push_back(std::make_pair(150, 150));
	m_powerUpSpawnPoints.push_back(std::make_pair(474, 194));
	m_powerUpSpawnPoints.push_back(std::make_pair(140, 370));
	m_powerUpSpawnPoints.push_back(std::make_pair(69, 463));
	m_powerUpSpawnPoints.push_back(std::make_pair(153, 555));
	m_powerUpSpawnPoints.push_back(std::make_pair(308, 571));
	m_powerUpSpawnPoints.push_back(std::make_pair(436, 464));
	m_powerUpSpawnPoints.push_back(std::make_pair(588, 378));
	m_powerUpSpawnPoints.push_back(std::make_pair(630, 557));
	m_powerUpSpawnPoints.push_back(std::make_pair(548, 630));
	m_powerUpSpawnPoints.push_back(std::make_pair(459, 548));
	m_powerUpSpawnPoints.push_back(std::make_pair(572, 269));
	m_powerUpSpawnPoints.push_back(std::make_pair(598, 74));
	m_powerUpSpawnPoints.push_back(std::make_pair(359, 214));
	m_powerUpSpawnPoints.push_back(std::make_pair(408, 294));	
	m_powerUpSpawnPoints.push_back(std::make_pair(305, 294));
}

unsigned short Engine::getStarsCollected() const
{
	return m_starsCollected;
}

void Engine::setStarsCollected(unsigned short stars)
{
	m_starsCollected = stars;
}

Animation Engine::createExplosionAnimation()
{
	Animation explosionAnimation;
	explosionAnimation.setSpriteSheet(m_explosionTextureSheet);
	
	for (int i = 0; i < 5; i++)
		explosionAnimation.addFrame(sf::IntRect(0, i * 48, 48, 48));

	return explosionAnimation;
}

Animation Engine::createSpawnAnimation()
{
	Animation spawnAnimation;
	spawnAnimation.setSpriteSheet(m_spawnAnimTextureSheet);

	for (int i = 0; i < 10; i++)
		spawnAnimation.addFrame(sf::IntRect(0, i * 31, 33, 31));

	return spawnAnimation;
}

void Engine::setGameOver(bool gameOver)
{
	m_gameOver = gameOver;
}


void Engine::setUpWorld(unsigned short stage)
{
	logger.Logi(Logger::Level::Info, "Game Started");
	unsigned short x = 0;
	unsigned short y = 0;
	float worldEntitySize = 48;
	std::vector<std::string> fileNames = { "../stages/stage1.txt", "../stages/stage2.txt", "../stages/stage3.txt", "../stages/stage4.txt", "../stages/stage5.txt"
	, "../stages/stage6.txt", "../stages/stage7.txt", "../stages/stage8.txt", "../stages/stage9.txt", "../stages/stage10.txt", "../stages/stage11.txt", "../stages/stage12.txt"
	, "../stages/stage13.txt", "../stages/stage14.txt", "../stages/stage15.txt", "../stages/stage16.txt", "../stages/stage17.txt", "../stages/stage18.txt", 
		"../stages/stage19.txt", "../stages/stage20.txt" , "../stages/stage21.txt", "../stages/stage22.txt" };
	std::string inputFromFile;
	std::ifstream file(fileNames.at(stage));

	while (std::getline(file, inputFromFile)) {
		x = 0;
		for (auto chr : inputFromFile) {

			switch (chr) {
				case 'w': {

					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::WorldBound, x * worldEntitySize + worldEntitySize / 2, y * worldEntitySize + worldEntitySize / 2));
					break;
				}
				case 'b': {
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Brick, x * worldEntitySize, y * worldEntitySize));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Brick, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Brick, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Brick, x * worldEntitySize, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Brick, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Brick, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Brick, x * worldEntitySize, y * worldEntitySize + worldEntitySize / 3));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Brick, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + worldEntitySize / 3));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Brick, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + worldEntitySize / 3));
					break;
				}
				case 's': {
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Steel, x * worldEntitySize, y * worldEntitySize));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Steel, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Steel, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Steel, x * worldEntitySize, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Steel, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Steel, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Steel, x * worldEntitySize, y * worldEntitySize + worldEntitySize / 3));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Steel, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + worldEntitySize / 3));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Steel, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + worldEntitySize / 3));
					break;
				}
				case 'e': {
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Eagle, x * worldEntitySize + worldEntitySize / 2, y * worldEntitySize + worldEntitySize / 2));
					break;
				}
				case ' ': {

					break;
				}
				case 'g': {
					m_bushVec.push_back(std::make_unique<WorldEntity>(entityType::Bush, x * worldEntitySize, y * worldEntitySize));
					m_bushVec.push_back(std::make_unique<WorldEntity>(entityType::Bush, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize));
					m_bushVec.push_back(std::make_unique<WorldEntity>(entityType::Bush, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize));
					m_bushVec.push_back(std::make_unique<WorldEntity>(entityType::Bush, x * worldEntitySize, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_bushVec.push_back(std::make_unique<WorldEntity>(entityType::Bush, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_bushVec.push_back(std::make_unique<WorldEntity>(entityType::Bush, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_bushVec.push_back(std::make_unique<WorldEntity>(entityType::Bush, x * worldEntitySize, y * worldEntitySize + worldEntitySize / 3));
					m_bushVec.push_back(std::make_unique<WorldEntity>(entityType::Bush, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + worldEntitySize / 3));
					m_bushVec.push_back(std::make_unique<WorldEntity>(entityType::Bush, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + worldEntitySize / 3));
					break;
				}
				case 'i': {
					m_iceVec.push_back(std::make_unique<WorldEntity>(entityType::Ice, x * worldEntitySize, y * worldEntitySize));
					m_iceVec.push_back(std::make_unique<WorldEntity>(entityType::Ice, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize));
					m_iceVec.push_back(std::make_unique<WorldEntity>(entityType::Ice, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize));
					m_iceVec.push_back(std::make_unique<WorldEntity>(entityType::Ice, x * worldEntitySize, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_iceVec.push_back(std::make_unique<WorldEntity>(entityType::Ice, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_iceVec.push_back(std::make_unique<WorldEntity>(entityType::Ice, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_iceVec.push_back(std::make_unique<WorldEntity>(entityType::Ice, x * worldEntitySize, y * worldEntitySize + worldEntitySize / 3));
					m_iceVec.push_back(std::make_unique<WorldEntity>(entityType::Ice, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + worldEntitySize / 3));
					m_iceVec.push_back(std::make_unique<WorldEntity>(entityType::Ice, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + worldEntitySize / 3));
					break;
				}
				case 'a': {
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Water, x * worldEntitySize, y * worldEntitySize));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Water, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Water, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Water, x * worldEntitySize, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Water, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Water, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + 2 * (worldEntitySize / 3)));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Water, x * worldEntitySize, y * worldEntitySize + worldEntitySize / 3));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Water, x * worldEntitySize + worldEntitySize / 3, y * worldEntitySize + worldEntitySize / 3));
					m_worldEntities.push_back(std::make_unique<WorldEntity>(entityType::Water, x * worldEntitySize + 2 * (worldEntitySize / 3), y * worldEntitySize + worldEntitySize / 3));
					break;
				}
				case 'h': {
					m_enemyTanks.push_back(std::make_unique<Enemy>(x * worldEntitySize + worldEntitySize / 2, y * worldEntitySize + worldEntitySize / 2, false));
					m_enemySpawnPoints.push_back(std::make_pair(x * worldEntitySize + worldEntitySize / 2, y * worldEntitySize + worldEntitySize / 2));
					break;
				}
				case 'p': {
					m_localPlayerTank = std::make_unique<Tank>(x * worldEntitySize + worldEntitySize / 2, y * worldEntitySize + worldEntitySize / 2);
					m_localPlayerSpawnPoint.first = x * worldEntitySize + worldEntitySize / 2;
					m_localPlayerSpawnPoint.second = y * worldEntitySize + worldEntitySize / 2;
				}
			}

			x++;
		}
		y++;
	}
	logger.Logi(Logger::Level::Info, m_worldEntities.size(), " elements were loaded in this stage ");

}


