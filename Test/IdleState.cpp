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
	if (GetAsyncKeyState('1') & 0x8000)
		player.SetWeapon(SWORD);
	if (GetAsyncKeyState('2') & 0x8000)
		player.SetWeapon(PISTOL);
	if (GetAsyncKeyState('3') & 0x8000)
		player.SetWeapon(RIFLE);
	if (GetAsyncKeyState('4') & 0x8000)
		player.SetWeapon(SHOTGUN);
	if (GetAsyncKeyState('5') & 0x8000)
		player.SetWeapon(ROCKET);
	if (GetAsyncKeyState('6') & 0x8000)
		player.SetWeapon(GRENADE);
	player.SetDirection();
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		player.attack();
	if (isMove) {
		player.SetDir(Vector2D<float>(dirX, dirY));
		return new RunState();
	}
	return nullptr;
}

void IdleState::update(Player& player)
{
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
