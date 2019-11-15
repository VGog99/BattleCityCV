#include "Bush.h"


Bush::Bush()
{
	setCanAdvance(true);
	setCanShootThrough(true);
	setIsBreakable(false);
	setCanHideTank(true);
	bushTexture.loadFromFile("../resources/bush.png");
}

Bush::~Bush()
{

}

void Bush::drawBush()
{
	//deseneaza tufisuri
}

sf::Sprite Bush::createSprite()
{

	sf::Sprite sprite(bushTexture);
	return sprite;
}