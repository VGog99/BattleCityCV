#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <algorithm>

class Menu
{
public:
	Menu();
	~Menu();

	bool getIsInMenu() const;
	void setIsInMenu(const bool set);
	int getMenuOption() const;
	void setMenuOption(const int option);
	void setStageChooser(const bool stageChooser);
	bool getStageChooser() const;
	void setPaused(const bool pause);
	bool getPaused() const;
	void setScore(sf::Text score);
	void updateSprites();
	void drawStageChangeScene(sf::RenderWindow& window, unsigned int currentStage, sf::Clock& clock, bool& shouldDraw);
	void setGameOverSprite(sf::Sprite gameOverSprite);
	void setFirstPlayerLivesText(unsigned short lives);

	sf::Text getScore();
	sf::Sprite createSprite();
	sf::Sprite getGameOverSprite() const;

	sf::Text getStartText();
	sf::Text getOnePlayerText();
	sf::Text getTwoPlayersText();
	sf::Sprite getMenuSprite();
	sf::Sprite getTankSprite();
	sf::Text getExitText();
	sf::Text getStageText();
	sf::Text getPauseText();
	sf::Text getCurrentStageText();
	sf::Text getFirstPlayerText();
	sf::Text getFirstPlayerLivesText();
	sf::Font getMenuFont();
	sf::Sprite getStageFlag();

public:
	sf::Texture m_gameOverTexture;
	sf::Sprite m_gameOverSprite;
	sf::Text scoreDisplay;

private:

	bool m_isInMenu = true;
	bool m_isPaused = false;
	sf::Texture titleTexture;
	int m_menuOption = 0;
	bool m_stageChooser = false;
	float secondCounter = 0.f;

	sf::Font menuFont;
	sf::Text startText;
	sf::Text onePlayerText;
	sf::Text twoPlayersText;

	sf::Text exitText;
	sf::Text pauseText;
	sf::Text stageText;
	sf::Text currentStageText;
	sf::Text firstPlayerText;
	sf::Text firstPlayerLivesText;

	sf::Sprite menuSprite;
	sf::Texture tankTexture;
	sf::Sprite tankSprite;
	sf::Text gameOver;
	sf::Text m_score;
	sf::RectangleShape grayBackground;
	sf::Texture stageFlag;
	sf::Sprite stageFlagSprite;

};
