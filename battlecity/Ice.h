#pragma once
#include "Tile.h"
#include "Tank.h"
class Ice :public Tile, public Tank
{private:
	sf::Texture iceTexture;
	const double speedBoost=2.0;
public:
	Ice();
	~Ice();
	sf::Sprite createSprite();
};

