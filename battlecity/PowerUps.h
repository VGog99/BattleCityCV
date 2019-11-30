#pragma once
#include "Tile.h"
class PowerUps : public Tile
{
private: 
	enum bonus
	{
		Tank=0,
		Star=1,
		Bomb=2,
		Clock=3,
		Shovel=4,
		Shield=5
	};
	sf::Texture TankPUTexture;
	sf::Texture StarPUTexture;
	sf::Texture BombPUTexture;
	sf::Texture ClockPUTexture;
	sf::Texture ShovelPUTexture;
	sf::Texture ShieldPUTexture;

public:
	PowerUps();
	sf::Sprite createSprite(bonus b);
	~PowerUps();
	sf::Sprite createSprite();
};

