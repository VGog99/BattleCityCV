#pragma once
class Tile
{ 
protected:
	static const int m_width=25;
	static const int m_height=25;
	bool m_advance, m_breakeble, m_canHide, m_shootThrough;
	Tile();
	Tile(const Tile&);
	Tile& operator = (const Tile&);//fiind proteced constructorul, constructorul de copiere si supraincarcarea op egal se va preveni orice incercare de instantiere
public:
	virtual bool getCanAdvance() const=0;
	virtual bool getIsBrakeble() const=0;
	virtual bool getCanHideTank() const=0;
	virtual bool getIsShootThrough() const = 0;
	virtual void setCanAdvance(const bool advance)=0;
	virtual void setIsBreakeble(const bool brakeble)=0;
	virtual void setCanHideTank(const bool canHide)=0;
	virtual void setIsShootThrough(const bool shootThrough) = 0;
	virtual ~Tile();
};

