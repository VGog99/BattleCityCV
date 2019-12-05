#pragma once

#include "Object.h"

class Eagle : public Object
{

private:

	bool m_isEagleAlive;
	sf::Texture eagleTexture;

public:

	Eagle();
	bool getIsEagleAlive() const;
	void setIsEagleAlive(const bool isEagleAlive);
	sf::Sprite createSprite();
	std::string getType() const;

};


