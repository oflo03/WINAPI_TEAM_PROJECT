#pragma once
#include"Weapon.h"

class Pistol :public Weapon
{
public:
	Pistol() :Weapon() {
		coolTime = cooltime[PISTOL];
		curAmmo = 10;
		damage = 20;
		resource.Load(L"Item_Weapon_Pistol.png");
		reverseResource.Load(L"Item_Weapon_Pistol_Reverse.png");
	}
	virtual void update();
	virtual void attack(std::vector<Bullet*>& bullets, const Vector2D<float>& center);
};