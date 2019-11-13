#include "Water.h"



Water::Water()
{
	setIsBreakable(false);
	setCanAdvance(false);
	setCanHideTank(false);
	setCanShootThrough(true);
	waterTexture.loadFromFile("../resources/steel.png");
}


Water::~Water()
{

}
sf::Sprite Water::createSprite() 
{

	sf::Sprite sprite(waterTexture);
	return sprite;
}
