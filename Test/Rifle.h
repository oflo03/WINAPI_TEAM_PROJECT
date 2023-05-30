#pragma once
#include"Weapon.h"

class Rifle :public Weapon
{
private:
	int coolTime;
public:
	Rifle() :Weapon() {
		coolTime = cooltime[RIFLE];
		curAmmo = 10;
		damage = 20;
		resource.Load(L"Item_Weapon_Rifle.png");
	}
	virtual void update();
	virtual void attack(const Vector2D<float>& center);
};