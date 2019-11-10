#pragma once
#include "Tile.h"
class Steel :public Tile
{
public:
	Steel();
	void setCanAdvance(const bool advance=0);//toti setteri vor pasa valuarea 0 si se vor apela in main fara parametru ex:setCanAdvance();
	void setIsBreakeble(const bool breakeble=0);
	void setCanHideTank(const bool canHide=0);
	void setIsShootThrough(const bool shootThrough=0);
    bool getCanAdvance() const;
	bool getIsBrakeble() const;
	bool getCanHideTank() const;
	bool getIsShootThrough() const;
	void drawSteel();//deseneaza cuburile de fier(nu se sparg)
	~Steel();
};

