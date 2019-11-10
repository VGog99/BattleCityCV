#include "Tile.h"

Tile::Tile()
{
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

void Tile::setCanTakeDamage(const bool canTakeDamage)
{
	m_canTakeDamage = canTakeDamage;
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

bool Tile::getCanTakeDamage() const
{
	return m_canTakeDamage;
}