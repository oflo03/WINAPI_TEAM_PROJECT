#pragma once
#include"Item.h"

class Weapon
	: public Item
{
protected:
	int curAmmo;
	int maxAmmo;
	int damage;
	double angle;
public:
	Weapon() :maxAmmo(0), damage(0),curAmmo(0), angle(0) {}
	~Weapon() {
		resource.Destroy();
	}
	virtual void draw_weapon(HDC mDC,const Vector2D<int>& center) = 0;
	virtual void update() = 0;
	virtual void attack() = 0;
	int GetCurAmmo() { return curAmmo; }
};
