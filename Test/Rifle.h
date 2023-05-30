#pragma once
#include"Weapon.h"

class Rifle :public Weapon
{
public:
	Rifle() :Weapon() {
		coolTime = cooltime[RIFLE];
		curAmmo = 10;
		damage = 20;
		resource.Load(L"Item_Weapon_Rifle.png");
		reverseResource.Load(L"Item_Weapon_Rifle_Reverse.png");
	}
	virtual void update();
	virtual void attack(std::vector<Bullet*>& bullets, const Vector2D<float>& center);
};