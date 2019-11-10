#include "Brick.h"
#include <iostream>



Brick::Brick()
{

	setCanAdvance(false);
	setCanHideTank(false);
	setCanShootThrough(false);
	setIsBreakable(true);
	brickTexture.loadFromFile("../resources/brick.png");
}

Brick::~Brick()
{

}


sf::Sprite Brick::createSprite() {

	sf::Sprite sprite(brickTexture);
	return sprite;
}