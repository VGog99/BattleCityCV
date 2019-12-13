#include "Tank.h"

Tank::Tank()
{
}

Tank::~Tank()
{
}

Tank::Tank(float posX, float posY) : m_tankPosition(std::make_pair(posX, posY))
{
	m_tankTexture.loadFromFile("../resources/tank.png");
}

sf::Texture Tank::getTexture() 
{
	return m_tankTexture;
}


