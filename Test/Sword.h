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
		resource.Load(L"sword.png");
	}
	virtual void draw_weapon(HDC mDC, const Vector2D<int>& center);
	virtual void update();
	virtual void attack();
};
