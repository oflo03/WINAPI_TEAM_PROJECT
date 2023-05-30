#pragma once
#include"Weapon.h"

class Pistol :public Weapon
{
private:
	int coolTime;
public:
	Pistol() :Weapon() {
		coolTime = cooltime[PISTOL];
		curAmmo = 10;
		damage = 20;
		resource.Load(L"Item_Weapon_Pistol.png");
	}
	virtual void update();
	virtual void attack(const Vector2D<float>& center);
};