#pragma once
#include "Tile.h"

class Road :public Tile
{

private:
	sf::Texture roadTexture;

public:
	Road();
	~Road();

	sf::Sprite createSprite();

};

