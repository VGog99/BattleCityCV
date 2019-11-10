#include "Brick.h"



Brick::Brick()
{
}
void Brick::setCanAdvance(bool advance)
{
	m_advance = advance;
}
void Brick::setCanHideTank(bool canHide)
{
	m_canHide = canHide;
}
void Brick::setIsBreakeble(bool breakeble)
{
	m_breakeble = breakeble;
}
void Brick::setIsShootThrough(bool shootThrough)
{
	m_shootThrough = shootThrough;
}
bool Brick::getCanAdvance() const
{
	return m_advance;
}
bool Brick::getCanHideTank() const
{
	return m_canHide;
}
bool Brick::getIsBrakeble() const
{
	return m_breakeble;
}
bool Brick::getIsShootThrough() const
{
	return m_shootThrough;
}
void Brick::drawBrick()
{
	//deseneaza casuta de caramida
}

Brick::~Brick()
{
}
