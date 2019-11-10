#include "Road.h"



Road::Road()
{

	setCanAdvance(true);
	setCanHideTank(false);
	setCanShootThrough(true);
	setIsBreakable(false);
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