#include "Ice.h"



Ice::Ice()
{
	setIsBreakable(false);
	setCanAdvance(true);
	setCanHideTank(false);
	setCanShootThrough(true);
	iceTexture.loadFromFile("../resources/ice.png");
}


Ice::~Ice()
{
}
sf::Sprite Ice::createSprite()
{

	sf::Sprite sprite(iceTexture);
	return sprite;
}

