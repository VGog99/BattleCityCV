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
	return isInMenu;
}

void Menu::setIsInMenu(const bool set)
{
	isInMenu = set;
}

sf::Sprite Menu::createSprite()
{
	sf::Sprite sprite(titleTexture);
	sprite.setPosition(50, 40);
	return sprite;
}

int Menu::getMenuOption() const
{
	return menuOption;
}

void Menu::setMenuOption(const int option)
{
	menuOption = option;
}

void Menu::setStageChooser(const bool stageChooser)
{
	this->stageChooser = stageChooser;
}

bool Menu::getStageChooser() const
{
	return stageChooser;
}

sf::Font Menu::getMenuFont()
{
	return menuFont;
}
