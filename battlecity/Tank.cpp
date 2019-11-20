#include "Tank.h"

Tank::Tank()
{
	tankTexture0.loadFromFile("../resources/playerOne0.png");
	tankTexture1.loadFromFile("../resources/playerOne1.png");
	tankTexture2.loadFromFile("../resources/playerOne2.png");
	tankTexture3.loadFromFile("../resources/playerOne3.png");
}

Tank::Tank(double posX, double posY, int speed, int damage, int direction) 
{
	this->m_speed = speed;
	this->m_damage = damage;
	this->direction = direction;
}
void Tank::setSpeed(unsigned int speed)
{
	m_speed = speed;
}
unsigned int Tank::getSpeed() const
{
	return m_speed;
}

sf::Sprite Tank::createSprite(int pos)
{
	switch (pos)
	{
	
	     case 0:
	     {
		       sf::Sprite sprite(tankTexture0);
			   return sprite;
		       break;
	     }
	     case 1:
	     {
		       sf::Sprite sprite(tankTexture1);
			   return sprite;
		       break;
	     }
	     case 2:
	     {
		       sf::Sprite sprite(tankTexture2);
			   return sprite;
		       break;
	     }
	     case 3:
	     {
		       sf::Sprite sprite(tankTexture3);
			   return sprite;
		       break;
	     }

	}
}