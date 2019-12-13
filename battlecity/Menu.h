#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <algorithm>

class Menu
{
private:

	bool isInMenu = true;
	bool isPaused = false;
	sf::Texture titleTexture;
	int menuOption = 0;
	bool stageChooser = false;
	sf::Font menuFont;

public:
	Menu();
	~Menu();

	bool getIsInMenu() const;
	void setIsInMenu(const bool set);
	sf::Sprite createSprite();

	int getMenuOption() const;
	void setMenuOption(const int option);

	void setStageChooser(const bool stageChooser);
	bool getStageChooser() const;

	void setPaused(const bool pause);
	bool getPaused() const;

	sf::Font getMenuFont();
};

