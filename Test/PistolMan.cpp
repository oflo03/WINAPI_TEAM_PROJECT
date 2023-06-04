#include "PistolMan.h"

PistolMan::PistolMan(double x, double y) : Enemy(x,y)
{
	weapon = new Pistol();

}

PistolMan::PistolMan(const PistolMan& other)
{
	weapon = new Pistol();
}


PistolMan::~PistolMan()
{
	delete weapon;
	DestroyImage();
}

void PistolMan::draw_character(HDC mDC)
{
}

void PistolMan::handle_event()
{
}

void PistolMan::update()
{
}

void PistolMan::SetImage(int state)
{
	switch (state)
	{
	case STATE_IDLE:
		animation[FRONT].resource.Load(L"enemy_pistol_right.png");
		animation[FRONT_RIGHT].resource.Load(L"enemy_pistol_right.png");
		animation[FRONT_LEFT].resource.Load(L"enemy_pistol_left.png");
		animation[BACK].resource.Load(L"enemy_pistol_back.png");
		animation[BACK_RIGHT].resource.Load(L"enemy_pistol_back.png");
		animation[BACK_LEFT].resource.Load(L"enemy_pistol_back.png");
		for (int i = 0; i < 6; i++) {
			animation[i].frame = 2;
			animation[i].size = { 0,0,animation[i].resource.GetWidth() / animation[i].frame,animation[i].resource.GetHeight() };
		}
		break;
	case STATE_RUN:
		animation[FRONT].resource.Load(L"enemy_pistol_run_front.png");
		animation[FRONT_RIGHT].resource.Load(L"enemy_pistol_run_right.png");
		animation[FRONT_LEFT].resource.Load(L"enemy_pistol_run_left.png");
		animation[BACK].resource.Load(L"enemy_pistol_run_back.png");
		animation[BACK_RIGHT].resource.Load(L"enemy_pistol_run_back.png");
		animation[BACK_LEFT].resource.Load(L"enemy_pistol_run_back.png");
		for (int i = 0; i < 6; i++) {
			animation[i].frame = 6;
			animation[i].size = { 0,0,animation[i].resource.GetWidth() / animation[i].frame,animation[i].resource.GetHeight() };
		}
		break;
	default:
		break;
	}
}

void PistolMan::SetDirection()
{
}

void PistolMan::attack()
{
}

void PistolMan::DestroyImage()
{
	for (int i = 0; i < 4; i++)
		animation[i].resource.Destroy();
}
