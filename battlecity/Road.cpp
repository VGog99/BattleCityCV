#include "Road.h"



Road::Road()
{

	setCanAdvance(true);
	setCanHideTank(false);
	setCanShootThrough(true);
	setHP(1);
	roadTexture.loadFromFile("../resources/road.png");
}

Road::~Road()
{

}

sf::Sprite Road::createSprite()
{
	sf::Sprite sprite(roadTexture);
	return sprite;
}

std::string Road::getType() const {
	return "road";
}