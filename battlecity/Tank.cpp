#include "Tank.h"

Tank::Tank()
{

}

Tank::Tank(double posX, double posY, int speed, int damage, int direction) 
{
	this->speed = speed;
	this->damage = damage;
	this->direction = direction;
}

void Tank::drawTank() 
{
	//deseneaza tank-ul
}