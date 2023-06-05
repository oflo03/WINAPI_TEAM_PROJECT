#include "IdleState.h"
#include"RunState.h"
#include"RollState.h"


IdleState::~IdleState()
{
}

PlayerState* IdleState::handle_event(Player& player)
{
	float dirX = 0, dirY = 0;
	bool isMove = false;

	if (GetAsyncKeyState('D')) {
		dirX = 1;
		isMove = true;
	}
	else if (GetAsyncKeyState('A')) {
		dirX = -1;
		isMove = true;
	}
	if (GetAsyncKeyState('W')) {
		dirY = -1;
		isMove = true;
	}
	else if (GetAsyncKeyState('S')) {
		dirY = 1;
		isMove = true;
	}
	if (GetAsyncKeyState('1') & 0x8000 && player.GetWeapon() != SWORD)
		player.SetWeapon(SWORD);
	if (GetAsyncKeyState('2') & 0x8000 && player.GetWeapon() != PISTOL)
		player.SetWeapon(PISTOL);
	if (GetAsyncKeyState('3') & 0x8000 && player.GetWeapon() != RIFLE)
		player.SetWeapon(RIFLE);
	if (GetAsyncKeyState('4') & 0x8000 && player.GetWeapon() != SHOTGUN)
		player.SetWeapon(SHOTGUN);
	if (GetAsyncKeyState('5') & 0x8000 && player.GetWeapon() != ROCKET)
		player.SetWeapon(ROCKET);
	player.SetDirection();
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		player.attack();
	if (GetAsyncKeyState(VK_RBUTTON) & 1) {}
	if (isMove) {
		player.SetDir(Vector2D<float>(dirX, dirY));
		return new RunState();
	}
	return nullptr;
}

void IdleState::update(Player& player)
{
	player.col->layer = 1;
	return;
}

void IdleState::enter(Player& player)
{
	player.SetImage(STATE_IDLE);
}

void IdleState::exit(Player& player)
{
	player.DestroyImage();
}
