#pragma once
class Tile
{ 
private:
	static const int m_width=25;
	static const int m_height=25;
	bool m_advance, m_breakeble, m_canHide;
public:
	Tile();
	bool getCanAdvance() const;
	bool getIsBrakeble() const;
	bool getCanHideTank() const;
	bool setCanAdvance(bool advance);
	bool setIsBreakeble(bool breakeble);
	bool setCanHideTank(bool canHide);
	~Tile();
};

