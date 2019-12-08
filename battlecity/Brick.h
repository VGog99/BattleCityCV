#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>

class Brick : public Object
{
private:
	//Conform docs: The texture must exist as long as the sprite uses it. Indeed, the sprite doesn't store its own copy of the texture
	sf::Texture brickTexture;

public:
	Brick();
	~Brick();

	sf::Sprite createSprite();
	std::string getType() const;

};

