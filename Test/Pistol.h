#pragma once
#include"Weapon.h"

class Pistol
	: public Weapon
{
public:
	Pistol();
	virtual void draw_weapon(HDC mDC);
	virtual void update();
	virtual void SetImage();
	virtual void attack();
};