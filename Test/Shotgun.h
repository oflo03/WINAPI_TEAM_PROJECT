#pragma once
#include"Weapon.h"

class Shotgun :public Weapon
{
public:
	Shotgun() :Weapon() {
		coolTime = cooltime[SHOTGUN];
		curAmmo = 10;
		damage = 20;
		resource.Load(L"Item_Weapon_Shotgun.png");
		reverseResource.Load(L"Item_Weapon_Shotgun_Reverse.png");
	}
	virtual void update();
	virtual void attack(std::vector<Bullet*>& bullets, const Vector2D<float>& center);
};