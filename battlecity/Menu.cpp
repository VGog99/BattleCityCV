#include "Menu.h"

Menu::Menu()
{
	titleTexture.loadFromFile("../resources/title.png");
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
