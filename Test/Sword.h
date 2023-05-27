#include "Weapon.h"
#include"Player.h"

class Sword : public Weapon
{
private:
	int coolTime;
public:
	Sword(int cooltime) :Weapon(), coolTime(cooltime){
		curAmmo = 1;
		damage = 20;
		resource.Load(L"Item_Weapon_Sword.png");
	}
	virtual void draw_weapon(HDC mDC);
	virtual void update();
	virtual void Attack();
};
