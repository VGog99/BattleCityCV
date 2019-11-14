#pragma once
#include "Tile.h"
#include "Tank.h"
class Ice :public Tile
{private:
	sf::Texture iceTexture;
public:
	Ice();
	~Ice();
	sf::Sprite createSprite();
};

