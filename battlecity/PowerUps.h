#pragma once
#include <SFML\Graphics.hpp>
#include "Macros.h"

enum powerUp {
	BombPU,
	ClockPU,
	ShieldPU,
	ShovelPU,
	StarPU,
	TankPU
};
class PowerUps
{
private:
	sf::Texture m_powerUpTexture;
	sf::Sprite m_powerUpSprite;
	powerUp m_powerUp;
	Position m_powerUpPosition;

public:
	PowerUps(powerUp type, float posX, float posY);
	powerUp getType() const;
	sf::Sprite getSprite() const;
};

