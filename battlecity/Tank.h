#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

using position = std::pair<double, double>;

class Tank : public Object
{

private:

	uint16_t m_speed;
	uint16_t m_damage;
	sf::Texture tankTexture;
	sf::Texture tankHiddenTexture;
	sf::Texture tankOnIceTexture;
	position m_position;
	char m_direction = DIR_UP;
	bool m_isMoving = false;
	std::pair<uint16_t, uint16_t> m_futurePosition;
	bool m_isHidden = false;
	bool m_isOnIce = false;

public:


	Tank(); //constructor default
	Tank(double posX, double posY, uint16_t speed, uint16_t damage, char direction); //constructor cu parametrii

	void setSpeed(uint16_t speed);
	uint16_t getSpeed() const;
	sf::Sprite createSprite();
	void setDirection(const char direction);
	char getDirection() const;
	std::string getType() const;
	bool getIsMoving() const;
	void setIsMoving(const bool isMoving);
	std::pair<uint16_t, uint16_t> getFuturePosition() const;
	void setFuturePosition(const std::pair<uint16_t, uint16_t> futurePosition);
	position getPosition() const;
	void setPosition(const position position);
	void setIsHidden(bool isHidden);
	bool getIsHidden() const;
	void setIsOnIce(bool isOnIce);
	bool getIsOnIce() const;

};

