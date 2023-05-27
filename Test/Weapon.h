#pragma once
#include "Item.h"

class Weapon
	: public Item
{
protected:
	int maxAmmo;
	int damage;
	int bulletType;
	double angle;
public:
	Weapon(int ma, int dmg, int bt) :maxAmmo(ma), damage(dmg), bulletType(bt) {}
	virtual void draw_weapon(HDC mDC) = 0;
	virtual void update() = 0;
	virtual void fire_weapon() = 0;
};