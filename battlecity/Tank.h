#pragma once
class Tank
{
public: 

	double posX;
	double posY;
	int direction;

	Tank(); //constructor default
	Tank(double posX, double posY, int speed ,int damage, int direction); //constructor cu parametrii
	void drawTank(); //deseneaza tank-ul

private:

	int speed;
	int damage;
};

