#pragma once
#include"Animation.h"

class Bullet
{
protected:
	Animation animation[6];
	int frame;
	double x;
	double y;
	int dirX;
	int dirY;
	int damage;
public:
	void SetX(double x) { this->x = x; }
	void SetY(double y) { this->y = y; }
	void SetDirX(int x) { this->dirX = x; }
	void SetDirY(int y) { this->dirY = y; }
	double GetX() { return x; }
	double GetY() { return y; }
	int GetDirX() { return dirX; }
	int GetDirY() { return dirY; }
	int GetDamage() { return damage; }
};