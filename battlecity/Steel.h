#pragma once
#include "Tile.h"

class Steel : public Tile
{

private:
	sf::Texture steelTexture;

public:
	Steel();
	~Steel();
	sf::Sprite createSprite(); 
	std::string getType() const;
};

