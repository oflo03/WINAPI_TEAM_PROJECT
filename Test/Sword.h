#include "Item.h"
#include"Player.h"

class Sword : public Item
{
private:
	int coolTime;
public:
	Sword(int cooltime) : coolTime(cooltime){
		resource.Load(L"Item_Weapon_Sword.png");
	}
	void Attack();
};
