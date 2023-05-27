#pragma once
#include"Item.h"

class Weapon
	: public Item
{
protected:
	int curAmmo;
	int maxAmmo;
	int type;
	double angle;
public:
	Weapon(int ma, int dmg, int type) :maxAmmo(ma), curAmmo(0), type(type), angle(0) {}
	virtual void draw_weapon(HDC mDC) = 0;
	virtual void update() = 0;
	virtual void SetImage() = 0;
	virtual void fire_weapon() = 0;
	int GetCurAmmo() { return curAmmo; }
};

#include"Pistol.h"