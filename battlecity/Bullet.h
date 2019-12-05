#pragma once
#include "Object.h"
#include "Macros.h"

class Bullet : public Object
{
private:
	sf::Texture bulletTexture;
	sf::Texture bulletOnWaterTexture;
	sf::Texture bulletOnIceTexture;
	char m_direction = DIR_UP;
	bool m_isOnWater = false;
	bool m_isOnIce = false;

public:
	Bullet();
	~Bullet();
	void setDirection(const char direction);
	char getDirection() const;
	sf::Sprite createSprite();
	std::string getType() const;
	bool getIsOnWater() const;
	void setIsOnWater(bool isOnWater);
	bool getIsOnIce() const;
	void setIsOnIce(bool isOnIce);

};

