#pragma once
#include "Tank.h"

class Enemy : public Tank
{

public:
	Enemy();
	Enemy(float posX, float posY);

	void doMovement();

};

