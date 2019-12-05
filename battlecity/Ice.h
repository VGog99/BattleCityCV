#pragma once
#include "Object.h"

class Ice :public Object
{

private:
	sf::Texture iceTexture;

public:
	Ice();
	~Ice();
	sf::Sprite createSprite();
	std::string getType() const;

};

