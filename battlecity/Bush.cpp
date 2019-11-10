#include "Bush.h"



Bush::Bush()
{
}
void Bush::setCanAdvance(const bool advance)
{
	m_advance = advance;
}
void Bush::setCanHideTank(const bool canHide)
{
	m_canHide = canHide;
}
void Bush::setIsBreakeble(const bool breakeble)
{
	m_breakeble = breakeble;
}
void Bush::setIsShootThrough(const bool shootThrough)
{
	m_shootThrough = shootThrough;
}
bool Bush::getCanAdvance() const
{
	return m_advance;
}
bool Bush::getCanHideTank() const
{
	return m_canHide;
}
bool Bush::getIsBrakeble() const
{
	return m_breakeble;
}
bool Bush::getIsShootThrough() const
{
	return m_shootThrough;
}
void Bush::drawBush()
{
	//deseneaza tufisuri
}

Bush::~Bush()
{
}
