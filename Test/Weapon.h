#pragma once
#include "Item.h"

class Weapon
	: public Item
{
protected:
	const int maxAmmo;
	const int damage;
	const int bulletType;
	double angle;
public:
	Weapon(int ma, int dmg) :maxAmmo(ma), damage(dmg) {}
	virtual void draw_weapon(HDC mDC) = 0;
	virtual void update() = 0;
	virtual void fire_weapon() = 0;
};