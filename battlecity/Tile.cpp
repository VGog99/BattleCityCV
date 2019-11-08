#include "Tile.h"



Tile::Tile()
{
}

bool Tile::getCanAdvance() const
{
	return m_advance;
}
bool Tile::getCanHideTank() const
{
	return m_canHide;
}
bool Tile::getIsBrakeble() const
{
	return m_breakeble;
}
bool Tile::setCanAdvance(bool advance)
{
	m_advance = advance;
}
bool Tile::setCanHideTank(bool canHide)
{
	m_canHide = canHide;
}
bool Tile::setIsBreakeble(bool breakeble)
{
	m_breakeble = breakeble;
}

Tile::~Tile()
{
}
