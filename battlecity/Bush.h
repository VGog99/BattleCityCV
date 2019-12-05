#pragma once
#include "Object.h"
class Bush :public Object
{

private:
	sf::Texture bushTexture;


public:
	Bush();
	~Bush();

	void drawBush(); //deseneaza tufisuri
	sf::Sprite createSprite();
	std::string getType() const;

};

