#pragma once
#include <SFML/Graphics.hpp>
//#include "SDK.h"
#include "Macros.h"

class Object
{

protected:
	bool m_advance;
	bool m_HP;
	bool m_canHide;
	bool m_canShootThrough;

	Object();
	Object(const Object&);
	Object& operator =(const Object&);

public:

	~Object();
	virtual sf::Sprite createSprite() = 0;
	virtual std::string getType() const = 0;
	bool getCanAdvance() const;
	int getHP() const;
	bool getCanHideTank() const;
	bool getCanShootThrough() const;
	void setCanAdvance(const bool advance);
	void setHP(const int HP);
	void setCanHideTank(const bool canHide);
	void setCanShootThrough(const bool shootThrough);
};

