#include "Weapon.h"
#include"Player.h"

class Sword : public Weapon
{
private:
	int coolTime;
public:
	Sword() :Weapon() {
		coolTime = cooltime[SWORD];
		curAmmo = 1;
		damage = 20;
		resource.Load(L"Item_Weapon_Sword.png");
	}
	virtual void update();
	virtual void attack(const Vector2D<float>& center);
};
