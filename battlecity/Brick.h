#pragma once
#include "Tile.h"
class Brick :public Tile
{
public:
	Brick();
	void setCanAdvance(const bool advance = 0);//toti setteri vor pasa valuarea indicata si se vor apela in main fara parametru ex:setCanAdvance();
	void setIsBreakeble(bool breakeble = 1);
	void setCanHideTank(bool canHide = 0);
	void setIsShootThrough(bool shootThrough = 0);
	bool getCanAdvance() const;
	bool getIsBrakeble() const;
	bool getCanHideTank() const;
	bool getIsShootThrough() const;
	void drawBrick();//deseneaza cuburile de caramida(se sparg)
	~Brick();
};

