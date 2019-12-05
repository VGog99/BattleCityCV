#pragma once
#include <SFML/Graphics.hpp>
//#include "SDK.h"
#include "Macros.h"

class Object
{

protected:



	Object();
	Object(const Object&);
	Object& operator =(const Object&);

public:

	~Object();
	virtual sf::Sprite createSprite() = 0;
	virtual std::string getType() const = 0;
};

