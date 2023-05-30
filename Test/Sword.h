#include "Weapon.h"
#include"Player.h"

class Sword : public Weapon
{
public:
	Sword() :Weapon() {
		coolTime = cooltime[SWORD];
		curAmmo = 1;
		damage = 20;
		resource.Load(L"Item_Weapon_Sword.png");
		reverseResource.Load(L"Item_Weapon_Sword_Reverse.png");
	}
	virtual void update();
	virtual void attack(std::vector<Bullet*>& bullets, const Vector2D<float>& center);
};
