#pragma once
#include "Tile.h"
#include <SFML/Graphics.hpp>

class Brick : public Tile
{
private:
	//Conform docs: The texture must exist as long as the sprite uses it. Indeed, the sprite doesn't store its own copy of the texture
	sf::Texture brickTexture;

public:
	Brick();
	~Brick();

	void drawBrick(); //deseneaza cuburile de caramida(se sparg)
	sf::Sprite createSprite();
};

