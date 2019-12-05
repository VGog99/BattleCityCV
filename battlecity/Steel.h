#pragma once
#include "Object.h"

class Steel : public Object
{

private:
	sf::Texture steelTexture;

public:
	Steel();
	~Steel();
	sf::Sprite createSprite(); 
	std::string getType() const;
};

