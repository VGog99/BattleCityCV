#include "Water.h"



Water::Water()
{
	setIsBreakable(false);
	setCanAdvance(false);
	setCanHideTank(false);
	setCanShootThrough(true);
	waterTexture.loadFromFile("../resources/water.png");
}


Water::~Water()
{

}
sf::Sprite Water::createSprite() 
{

	sf::Sprite sprite(waterTexture);
	return sprite;
}

std::string Water::getType() {
	return "water";
}