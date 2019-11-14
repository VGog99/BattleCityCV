#pragma once
#include <string>

class Player
{
private:
	std::string m_name;	
	char m_direction;	

public:
	Player();
	~Player();

	std::string getPlayerName() const;
	void setPlayerName(const std::string name);
	void setDirection(const char direction);
	char getDirection() const;

};

