#include "Menu.h"
#include <iostream>
Menu::Menu()
{
	titleTexture.loadFromFile("../resources/title.png");
	tankTexture.loadFromFile("../resources/tank.png");
	m_gameOverTexture.loadFromFile("../resources/gameOver.png");
	stageFlag.loadFromFile("../resources/stageFlag.png");
	stageFlagSprite.setTexture(stageFlag);
	stageFlagSprite.setPosition(sf::Vector2f(733, 570));

	m_gameOverSprite.setTexture(m_gameOverTexture);
	m_gameOverSprite.setPosition(300, 0);

	if (!menuFont.loadFromFile("../resources/font.ttf"))
	{
		// error...
		std::cout << "eroare";
	}

	scoreDisplay.setFont(menuFont);
	scoreDisplay.setCharacterSize(30);
	scoreDisplay.setStyle(sf::Text::Bold);
	scoreDisplay.setFillColor(sf::Color::White);
	scoreDisplay.setPosition(200, 500);

	menuSprite = createSprite();
	startText = sf::Text("START", menuFont);
	onePlayerText = sf::Text("1 PLAYERS", menuFont);
	twoPlayersText = sf::Text("2 PLAYERS", menuFont);
	exitText = sf::Text("EXIT", menuFont);
	pauseText = sf::Text("PAUSED", menuFont);
	currentStageText = sf::Text("1", menuFont, 30);
	currentStageText.setPosition(sf::Vector2f(770, 625));
	currentStageText.setFillColor(sf::Color(0, 0, 0, 255));

	firstPlayerText = sf::Text("IP", menuFont, 30);
	firstPlayerText.setPosition(sf::Vector2f(730, 365));
	firstPlayerText.setFillColor(sf::Color(0, 0, 0, 255));

	firstPlayerLivesText = sf::Text("", menuFont, 30);
	firstPlayerLivesText.setPosition(sf::Vector2f(730, 400));
	firstPlayerLivesText.setFillColor(sf::Color(0, 0, 0, 255));

	grayBackground.setSize(sf::Vector2f(900, 720));		
	grayBackground.setFillColor(sf::Color(127, 127, 127, 255));
	grayBackground.setPosition(sf::Vector2f(0, 0));

	tankSprite.setTexture(tankTexture);
	tankSprite.setOrigin(sf::Vector2f(tankTexture.getSize().x * 0.5, tankTexture.getSize().y * 0.5));
	tankSprite.setRotation(90.f);

	//startText.setPosition(387, 350);
	onePlayerText.setPosition(337, 350);
	twoPlayersText.setPosition(337, 420);
	exitText.setPosition(402, 490);
	pauseText.setPosition(370, 360);

}

Menu::~Menu()
{

}

sf::Text Menu::getStartText() {
	return startText;
}

sf::Text Menu::getOnePlayerText()
{
	return onePlayerText;
}

sf::Text Menu::getTwoPlayersText()
{
	return twoPlayersText;
}

sf::Sprite Menu::getMenuSprite()
{
	return menuSprite;
}

sf::Sprite Menu::getTankSprite()
{
	return tankSprite;
}

sf::Text Menu::getExitText()
{
	return exitText;
}

sf::Text Menu::getStageText()
{
	return stageText;
}

sf::Text Menu::getPauseText()
{
	return pauseText;
}

sf::Text Menu::getCurrentStageText()
{
	return currentStageText;
}

sf::Text Menu::getFirstPlayerText()
{
	return firstPlayerText;
}

sf::Text Menu::getFirstPlayerLivesText()
{
	return firstPlayerLivesText;
}

void Menu::setFirstPlayerLivesText(unsigned short lives)
{
	firstPlayerLivesText.setString(lives < 10 ? "0" + std::to_string(lives) : std::to_string(lives));
}

bool Menu::getIsInMenu() const
{
	return m_isInMenu;
}

void Menu::setIsInMenu(const bool set)
{
	m_isInMenu = set;
}

sf::Sprite Menu::createSprite()
{
	sf::Sprite sprite(titleTexture);
	sprite.setPosition(240, 60);
	return sprite;
}

int Menu::getMenuOption() const
{
	return m_menuOption;
}

void Menu::setMenuOption(const int option)
{
	m_menuOption = option;
}

void Menu::setStageChooser(const bool stageChooser)
{
	this->m_stageChooser = stageChooser;
}

bool Menu::getStageChooser() const
{
	return m_stageChooser;
}

void Menu::setPaused(const bool pause)
{
	m_isPaused = pause;
}

bool Menu::getPaused() const
{
	return m_isPaused;
}

void Menu::setScore(sf::Text score)
{
	m_score = score;
}

sf::Text Menu::getScore()
{
	return m_score;
}

sf::Sprite Menu::getGameOverSprite() const
{
	return m_gameOverSprite;
}

void Menu::setGameOverSprite(sf::Sprite gameOverSprite) {
	m_gameOverSprite = gameOverSprite;
}

void Menu::updateSprites()
{
	if (getMenuOption() == 0) {
		tankSprite.setPosition(onePlayerText.getPosition().x - 35, onePlayerText.getPosition().y + 15);
	}
	else if (getMenuOption() == 1) {
		tankSprite.setPosition(twoPlayersText.getPosition().x - 35, twoPlayersText.getPosition().y + 15);
	}
	else {
		tankSprite.setPosition(exitText.getPosition().x - 35, exitText.getPosition().y + 15);
	}
}

void Menu::drawStageChangeScene(sf::RenderWindow& window, unsigned int currentStage, sf::Clock& clock, bool& shouldDraw)
{
	sf::Time elapsed = clock.restart();
	secondCounter += elapsed.asSeconds();
	std::string stageNumberText = "STAGE " + std::to_string(currentStage + 1);
	currentStageText.setString(std::to_string(currentStage + 1));

	stageText = sf::Text(stageNumberText, menuFont);
	stageText.setCharacterSize(35);
	stageText.setPosition(330, 320);
	stageText.setFillColor(sf::Color::Black);

	if (secondCounter <= 3) {
		window.draw(grayBackground);
		window.draw(stageText);
	}
	else {
		secondCounter = 0;
		shouldDraw = false;
	}
}

sf::Font Menu::getMenuFont()
{
	return menuFont;
}

sf::Sprite Menu::getStageFlag()
{
	return stageFlagSprite;
}
