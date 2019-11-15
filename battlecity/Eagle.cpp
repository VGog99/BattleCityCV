#include "Eagle.h"

Eagle::Eagle()
{
	m_advance = false;
	m_breakable = true;
	m_canHide = false;
	m_canShootThrough = false;
	m_isEagleAlive = true;
	eagleTexture.loadFromFile("../resources/eagle.png");
}

bool Eagle::getIsEagleAlive() const
{
	return m_isEagleAlive;
}

void Eagle::setIsEagleAlive(const bool isEagleAlive)
{
	m_isEagleAlive = isEagleAlive;
}

sf::Sprite Eagle::createSprite()
{

	sf::Sprite sprite(eagleTexture);
	return sprite;
}