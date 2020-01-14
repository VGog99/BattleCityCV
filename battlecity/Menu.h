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
	sf::Text onePlayerText;
	sf::Text twoPlayersText;

	sf::Text exitText;
	sf::Text pauseText;
	sf::Text stageText;
	sf::Text stageOne;
	sf::Text stageTwo;
	sf::Text stageThree;
	sf::Text stageFour;
	sf::Sprite menuSprite;
	sf::Texture tankTexture;
	sf::Sprite tankSprite;
	sf::Text gameOver;

public:
	Menu();
	~Menu();

	sf::Texture m_gameOverTexture;
	sf::Sprite m_gameOverSprite;

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

	void setGameOverSprite(sf::Sprite gameOverSprite);
	sf::Sprite getGameOverSprite() const;

	sf::Text getStartText();
	sf::Text getOnePlayerText();
	sf::Text getTwoPlayersText();
	sf::Sprite getMenuSprite();
	sf::Sprite getTankSprite();
	sf::Text getExitText();
	sf::Text getStageText();
	sf::Text getStageOneText();
	sf::Text getStageTwoText();
	sf::Text getStageThreeText();
	sf::Text getStageFourText();
	sf::Text getPauseText();
	sf::Font getMenuFont();
};
