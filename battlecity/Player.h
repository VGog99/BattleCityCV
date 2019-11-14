#pragma once
#include <string>

class Player
{
private:
	std::string m_name;	
	uint8_t m_direction;	

public:
	Player();
	~Player();

	std::string getPlayerName() const;
	void setPlayerName(const std::string name);
	void setDirection(const uint8_t direction);

};

