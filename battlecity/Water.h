#pragma once
#include "Tile.h"
class Water : public Tile
{private:
	sf::Texture waterTexture;
public:
	Water();
	~Water();
	sf::Sprite createSprite();
	std::string getType() const;

};
