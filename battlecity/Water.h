#pragma once
#include "Object.h"
class Water : public Object
{
private:
	sf::Texture waterTexture;
public:
	Water();
	~Water();
	sf::Sprite createSprite();
	std::string getType() const;

};
