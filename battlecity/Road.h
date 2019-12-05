#pragma once
#include "Object.h"

class Road :public Object
{

private:
	sf::Texture roadTexture;

public:
	Road();
	~Road();

	sf::Sprite createSprite();
	std::string getType() const;
};

