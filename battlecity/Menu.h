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

	sf::Text startText;
	sf::Text exitText;
	sf::Text pauseText;
	sf::Text stageText;
	sf::Text stageOne;
	sf::Text stageTwo;
	sf::Text stageThree;
	sf::Text stageFour;
	sf::Sprite menuSprite;

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

	void updateMenuColor();

	sf::Text getStartText();
	sf::Sprite getMenuSprite();
	sf::Text getExitText();
	sf::Text getStageText();
	sf::Text getStageOneText();
	sf::Text getStageTwoText();
	sf::Text getStageThreeText();
	sf::Text getStageFourText();
	sf::Text getPauseText();

	sf::Font getMenuFont();
};
