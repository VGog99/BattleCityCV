#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <algorithm>

class Menu
{
private:

	bool m_isInMenu = true;
	bool m_isPaused = false;
	sf::Texture titleTexture;
	int m_menuOption = 0;
	bool m_stageChooser = false;
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
