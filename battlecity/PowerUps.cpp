#include "PowerUps.h"



PowerUps::PowerUps(powerUp type, float posX, float posY): m_powerUp(type), m_powerUpPosition(std::make_pair(posX, posY))
{
	switch (type) {
	case powerUp::BombPU:
	{
		m_powerUpTexture.loadFromFile("../resources/BombPUTexture.png");
		break;
	}
	case powerUp::ClockPU:
	{
		m_powerUpTexture.loadFromFile("../resources/ClockPUTexture.png");
		break;
	}
	case powerUp::ShieldPU:	
	{
		m_powerUpTexture.loadFromFile("../resources/ShieldPUTexture.png");
		break;
	}
	case powerUp::ShovelPU:
	{
		m_powerUpTexture.loadFromFile("../resources/ShovelPUTexture.png");
		break;
	}
	case powerUp::StarPU:
	{
		m_powerUpTexture.loadFromFile("../resources/StarPUTexture.png");
		break;
	}
	case powerUp::TankPU:
	{
		m_powerUpTexture.loadFromFile("../resources/TankPUTexture.png");
		break;
	}
	}
}
powerUp PowerUps::getType() const
{
	return m_powerUp;
}

sf::Sprite PowerUps::getSprite() const
{
	return m_powerUpSprite;
}
