#pragma once
#include "Tile.h"
class Bush :public Tile
{

private:
	sf::Texture bushTexture;


public:
	Bush();
	~Bush();

	void drawBush(); //deseneaza tufisuri
	//sf::Sprite createSprite();

};

