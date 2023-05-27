#pragma once
#include"Animation.h"

const int BulletDamage[]{ 0,10,7,4 };

class Bullet
{
protected:
	Animation animation;
	int frame;
	double x;
	double y;
	int dirX;
	int dirY;
	int damage;
	int type;
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
	Bullet(int type, int x, int y, int dx, int dy) :type(type), x(x), y(y), dirX(dx), dirY(dy), damage(BulletDamage[type]), frame(0) { SetImage(type); }
	void SetImage(int type);
	void draw_bullet(HDC mDC);
	void update();
	void change_frame();
};