#pragma once
#include "Tile.h"

class Ice :public Tile
{

private:
	sf::Texture iceTexture;

public:
	Ice();
	~Ice();
	sf::Sprite createSprite();
	std::string getType() const;

};

