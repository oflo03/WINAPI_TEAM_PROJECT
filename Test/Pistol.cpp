#include"Pistol.h"


Pistol::Pistol() :Weapon(17, 10, PISTOL)
{

}

void Pistol::draw_weapon(HDC mDC)
{

}
void Pistol::update()
{

}
void Pistol::SetImage()
{
	this->resource.Load(L"Item_Weapon_Pistol.png");
}
void Pistol::attack()
{

}