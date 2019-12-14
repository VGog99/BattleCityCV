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

}

Menu::~Menu()
{

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

sf::Font Menu::getMenuFont()
{
	return menuFont;
}
