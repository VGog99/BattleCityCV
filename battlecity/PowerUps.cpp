#include "PowerUps.h"



PowerUps::PowerUps()
{
	setIsBreakable(false);
	setCanAdvance(true);
	setCanHideTank(false);
	setCanShootThrough(true);
	TankPUTexture.loadFromFile("../resources/TankPUTexture.png");
	StarPUTexture.loadFromFile("../resources/StarPUTexture.png");
	BombPUTexture.loadFromFile("../resources/BombPUTexture.png");
	ClockPUTexture.loadFromFile("../resources/ClockPUTexture.png");
	ShovelPUTexture.loadFromFile("../resources/ShovelPUTexture.png");
	ShieldPUTexture.loadFromFile("../resources/ShieldPUTexture.png");

}
sf::Sprite PowerUps::createSprite(bonus b)
{
	bonus b = bonus::Tank;
	switch (b)
	{
		case 0:
		{
			sf::Sprite sprite(TankPUTexture);
			return sprite;
			break;
		}
		case 1:
		{
			sf::Sprite sprite(StarPUTexture);
			return sprite;
			break;
		}
		case 2:
		{
			sf::Sprite sprite(BombPUTexture);
			return sprite;
			break;
		}
		case 3:
		{
			sf::Sprite sprite(ClockPUTexture);
			return sprite;
			break;
		}
		case 4:
		{
			sf::Sprite sprite(ShovelPUTexture);
			return sprite;
			break;
		}
		case 5:
		{
			sf::Sprite sprite(ShieldPUTexture);
			return sprite;
			break;
		}
	}
}

PowerUps::~PowerUps()
{
}
