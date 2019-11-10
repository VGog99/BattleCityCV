#pragma once
class Tile
{ 
protected:
	static const int m_width=25;
	static const int m_height=25;
	bool m_advance, m_breakable, m_canHide, m_canTakeDamage;
	Tile();
	Tile(const Tile&);
	Tile& operator = (const Tile&);//fiind protected constructorul, constructorul de copiere si supraincarcarea op egal se va preveni orice incercare de instantiere

public:
	bool getCanAdvance() const;
	bool getIsBreakable() const;
	bool getCanHideTank() const;
	bool getCanTakeDamage() const;
	void setCanAdvance(const bool advance);
	void setIsBreakable(const bool breakable);
	void setCanHideTank(const bool canHide);
	void setCanTakeDamage(const bool shootThrough);
	~Tile();
};

