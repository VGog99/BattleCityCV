#include "Steel.h"


Steel::Steel()
{
	setIsBreakable(false);
	setCanAdvance(false);
	setCanHideTank(false);
	setCanShootThrough(false);
	steelTexture.loadFromFile("../resources/steel.png");

}

Steel::~Steel()
{

}

sf::Sprite Steel::createSprite() 
{

	sf::Sprite sprite(steelTexture);
	return sprite;
}