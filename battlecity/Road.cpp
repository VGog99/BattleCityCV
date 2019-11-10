#include "Road.h"



Road::Road()
{
}
void Road::setCanAdvance(const bool advance)
{
	m_advance = advance;
}
void Road::setCanHideTank(const bool canHide)
{
	m_canHide = canHide;
}
void Road::setIsBreakeble(const bool breakeble)
{
	m_breakeble = breakeble;
}
void Road::setIsShootThrough(const bool shootThrough)
{
	m_shootThrough = shootThrough;
}
bool Road::getCanAdvance() const
{
	return m_advance;
}
bool Road::getCanHideTank() const
{
	return m_canHide;
}
bool Road::getIsBrakeble() const
{
	return m_breakeble;
}
bool Road::getIsShootThrough() const
{
	return m_shootThrough;
}
void Road::drawRoad()
{
	//deseneaza drum
}

Road::~Road()
{
}
