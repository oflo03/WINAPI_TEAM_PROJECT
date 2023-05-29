#pragma once
#include"Weapon.h"

class Pistol
	: public Weapon
{
public:
	Pistol();
	virtual void draw_weapon(HDC mDC, const Vector2D<float>& center);
	virtual void update();
	virtual void attack();
};