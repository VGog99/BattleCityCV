#pragma once
#include "Tile.h"
class Road :public Tile
{
public:
	Road();
	void setCanAdvance(const bool advance = 1);//toti setteri vor pasa valuarea indicata si se vor apela in main fara parametru ex:setCanAdvance();
	void setIsBreakeble(const bool breakeble = 0);
	void setCanHideTank(const bool canHide = 0);
	void setIsShootThrough(const bool shootThrough = 1);
	bool getCanAdvance() const;
	bool getIsBrakeble() const;
	bool getCanHideTank() const;
	bool getIsShootThrough() const;
	void drawRoad();//deseneaza casutele de drum
	~Road();
};

