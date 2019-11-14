#include "Tile.h"

Tile::Tile()
{
	m_advance = false;
	m_breakable = false;
	m_canShootThrough = false;
	m_canHide = false;
}

Tile::Tile(const Tile&)
{

}

Tile& Tile::operator = (const Tile&)
{
	return *this;
}

Tile::~Tile()
{
}

void Tile::setCanAdvance(const bool advance)
{
	m_advance = advance;
}

void Tile::setCanHideTank(const bool canHide)
{
	m_canHide = canHide;
}

void Tile::setIsBreakable(const bool breakable)
{
	m_breakable = breakable;
}

void Tile::setCanShootThrough(const bool canShootThrough)
{
	m_canShootThrough = canShootThrough;
}

bool Tile::getCanAdvance() const
{
	return m_advance;
}

bool Tile::getCanHideTank() const
{
	return m_canHide;
}

bool Tile::getIsBreakable() const
{
	return m_breakable;
}

bool Tile::getCanShootThrough() const
{
	return m_canShootThrough;
}