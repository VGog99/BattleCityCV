#pragma once
#include <SFML\Graphics.hpp>
#include <algorithm>

class Menu
{
private:

	bool isInMenu=true;
	sf::Texture titleTexture;
	int menuOption=0;
	sf::Font menuFont;

public:
	Menu();
	~Menu();

	bool getIsInMenu() const;
	void setIsInMenu(const bool set);
	sf::Sprite createSprite();

	int getMenuOption() const;
	void setMenuOption(const int option);

	sf::Font getMenuFont();
};

