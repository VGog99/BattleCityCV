#include "Menu.h"
#include <iostream>
Menu::Menu()
{
	titleTexture.loadFromFile("../resources/title.png");
	if (!menuFont.loadFromFile("../resources/font.ttf"))
	{
		// error...
		std::cout << "eroare";
	}

	menuSprite = createSprite();
	startText = sf::Text("Start", menuFont);
	exitText = sf::Text("Exit", menuFont);
	pauseText = sf::Text("Paused", menuFont);
	stageText = sf::Text("Choose your stage \n(use arrow keys)", menuFont);
	stageOne = sf::Text("Stage 1", menuFont);
	stageTwo = sf::Text("Stage 2", menuFont);
	stageThree = sf::Text("Stage 3", menuFont);
	stageFour = sf::Text("Stage 4", menuFont);

	startText.setPosition(287, 310);
	exitText.setPosition(302, 380);
	pauseText.setPosition(270, 360);
	stageText.setCharacterSize(25);
	stageText.setPosition(50, 150);
	stageOne.setCharacterSize(20);
	stageOne.setPosition(200, 250);
	stageTwo.setCharacterSize(20);
	stageTwo.setPosition(200, 300);
	stageThree.setCharacterSize(20);
	stageThree.setPosition(200, 350);
	stageFour.setCharacterSize(20);
	stageFour.setPosition(200, 400);
}

Menu::~Menu()
{

}

sf::Text Menu::getStartText() {
	return startText;
}

sf::Sprite Menu::getMenuSprite()
{
	return menuSprite;
}

sf::Text Menu::getExitText()
{
	return exitText;
}

sf::Text Menu::getStageText()
{
	return stageText;
}

sf::Text Menu::getStageOneText()
{
	return stageOne;
}

sf::Text Menu::getStageTwoText()
{
	return stageTwo;
}

sf::Text Menu::getStageThreeText()
{
	return stageThree;
}

sf::Text Menu::getStageFourText()
{
	return stageFour;
}

sf::Text Menu::getPauseText()
{
	return pauseText;
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
	sprite.setPosition(140, 60);
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

void Menu::updateMenuColor()
{
	startText.setFillColor(getMenuOption() ? sf::Color::White : sf::Color::Yellow);
	exitText.setFillColor(getMenuOption() ? sf::Color::Yellow : sf::Color::White);
	stageOne.setFillColor(getMenuOption() == 0 ? sf::Color::Yellow : sf::Color::White);
	stageTwo.setFillColor(getMenuOption() == 1 ? sf::Color::Yellow : sf::Color::White);
	stageThree.setFillColor(getMenuOption() == 2 ? sf::Color::Yellow : sf::Color::White);
	stageFour.setFillColor(getMenuOption() == 3 ? sf::Color::Yellow : sf::Color::White);
}

sf::Font Menu::getMenuFont()
{
	return menuFont;
}
