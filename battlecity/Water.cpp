#include "Water.h"



Water::Water()
{
	setHP(0);
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

std::string Water::getType() const{
	return "water";
}