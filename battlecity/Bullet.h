#pragma once
#include "Object.h"
#include "Macros.h"

class Bullet : public Object
{
private:
	sf::Texture bulletTexture;
	char m_direction = DIR_LEFT;

public:
	Bullet();
	~Bullet();
	void setDirection(const char direction);
	char getDirection() const;
	sf::Sprite createSprite();
	std::string getType() const;

};

