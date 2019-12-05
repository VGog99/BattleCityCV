#include "Object.h"



Object::Object()
{
	m_advance = false;
	m_HP= false;
	m_canShootThrough = false;
	m_canHide = false;
}
Object::Object(const Object&)
{

}
Object& Object::operator=(const Object&)
{
	return *this;
}
Object::~Object()
{
}
void Object::setCanAdvance(const bool advance)
{
	m_advance = advance;
}

void Object::setCanHideTank(const bool canHide)
{
	m_canHide = canHide;
}

void Object::setHP(const int HP)
{
	m_HP = HP;
}

void Object::setCanShootThrough(const bool canShootThrough)
{
	m_canShootThrough = canShootThrough;
}

bool Object::getCanAdvance() const
{
	return m_advance;
}

bool Object::getCanHideTank() const
{
	return m_canHide;
}

int Object::getHP() const
{
	return m_HP;
}

bool Object::getCanShootThrough() const
{
	return m_canShootThrough;
}
