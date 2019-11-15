#pragma once

#include "Tile.h"

class Eagle : public Tile
{

private:

	bool m_isEagleAlive;
	sf::Texture eagleTexture;

public:

	Eagle();
	bool getIsEagleAlive() const;
	void setIsEagleAlive(const bool isEagleAlive);
	sf::Sprite createSprite();

};


