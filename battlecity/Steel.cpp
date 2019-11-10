#include "Steel.h"



Steel::Steel()
{
}

void Steel::setCanAdvance(const bool advance)
{
	m_advance = advance;
}
void Steel::setCanHideTank(const bool canHide)
{
	m_canHide = canHide;
}
void Steel::setIsBreakeble(const bool breakeble)
{
	m_breakeble = breakeble;
}
void Steel::setIsShootThrough(const bool shootThrough)
{
	m_shootThrough = shootThrough;
}
bool Steel::getCanAdvance() const
{
	return m_advance;
}
bool Steel::getCanHideTank() const
{
	return m_canHide;
}
bool Steel::getIsBrakeble() const
{
	return m_breakeble;
}
bool Steel::getIsShootThrough() const
{
	return m_shootThrough;
}
void Steel::drawSteel()
{
	//deseneaza casuta de fier
}


Steel::~Steel()
{
}
