#include "Steel.h"


Steel::Steel()
{
	setHP(500);
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

std::string Steel::getType() const{
	return "steel";
}