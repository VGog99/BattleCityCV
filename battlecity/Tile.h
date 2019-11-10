#pragma once
#include <SFML/Graphics.hpp>

class Tile
{ 
protected:
	bool m_advance;
	bool m_breakable;
	bool m_canHide;
	bool m_canShootThrough;

	Tile();
	Tile(const Tile&);
	Tile& operator = (const Tile&); //fiind protected constructorul, constructorul de copiere si supraincarcarea op egal se va preveni orice incercare de instantiere

public:
	bool getCanAdvance() const;
	bool getIsBreakable() const;
	bool getCanHideTank() const;
	bool getCanShootThrough() const;
	void setCanAdvance(const bool advance);
	void setIsBreakable(const bool breakable);
	void setCanHideTank(const bool canHide);
	void setCanShootThrough(const bool shootThrough);
	virtual sf::Sprite createSprite() = 0;
	~Tile();
};

