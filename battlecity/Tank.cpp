#include "Tank.h"

Tank::Tank()
{
	tankTexture0.loadFromFile("../resources/playerOne0.png");
	tankTexture1.loadFromFile("../resources/playerOne1.png");
	tankTexture2.loadFromFile("../resources/playerOne2.png");
	tankTexture3.loadFromFile("../resources/playerOne3.png");
}

Tank::Tank(double posX, double posY, uint16_t speed, uint16_t damage, uint16_t direction): pos(posX,posY),m_speed(speed),m_damage(damage),m_direction(direction)
{
}
void Tank::setSpeed(uint16_t speed)
{
	m_speed = speed;
}
uint16_t Tank::getSpeed() const
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