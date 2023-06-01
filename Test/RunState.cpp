#include "RunState.h"
#include"IdleState.h"
#include"RollState.h"

extern double frame_time;

RunState::~RunState()
{
}

PlayerState* RunState::handle_event(Player& player)
{
	float dirX=0, dirY = 0;
	bool isMove = false;
	if (GetAsyncKeyState('D')) {
		dirX = 1;
		isMove = true;
	}
	else if (GetAsyncKeyState('A')) {
		dirX = -1;
		isMove = true;
	}
	else dirX = 0;
	if (GetAsyncKeyState('W')) {
		dirY = -1;
		isMove = true;
	}
	else if (GetAsyncKeyState('S')) {
		dirY = 1;
		isMove = true;
	}
	else dirY = 0;
	player.SetDirection();
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		player.attack();
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
		if (dirX == 1 && dirY == 0)
			player.SetDirection(FRONT_RIGHT);
		else if(dirX == 1 && dirY == 1)
			player.SetDirection(FRONT_RIGHT);
		else if (dirX == 0 && dirY == 1)
			player.SetDirection(FRONT);
		else if (dirX == -1 && dirY == 1)
			player.SetDirection(FRONT_LEFT);
		else if (dirX == -1 && dirY == 0)
			player.SetDirection(FRONT_LEFT);
		else if (dirX == -1 && dirY == -1)
			player.SetDirection(BACK_LEFT);
		else if (dirX == 0 && dirY == -1)
			player.SetDirection(BACK);
		else if (dirX == 1 && dirY == -1)
			player.SetDirection(BACK_RIGHT);
		player.SetDir(Vector2D<float>(0,0));
		return new RollState(dirX,dirY);
	}
	if (GetAsyncKeyState('1') & 0x8000)
		player.SetWeapon(SWORD);
	else if (GetAsyncKeyState('2') & 0x8000)
		player.SetWeapon(PISTOL);
	else if (GetAsyncKeyState('3') & 0x8000)
		player.SetWeapon(RIFLE);
	else if (GetAsyncKeyState('4') & 0x8000)
		player.SetWeapon(SHOTGUN);
	else if (GetAsyncKeyState('5') & 0x8000)
		player.SetWeapon(ROCKET);
	else if (GetAsyncKeyState('6') & 0x8000)
		player.SetWeapon(GRENADE);
	if (isMove) {
		player.SetDir(Vector2D<float>(dirX, dirY));
		return nullptr;
	}
	return new IdleState();
}

void RunState::update(Player& player)
{
	if (player.GetDir().GetLenth() == 1) {
		player.SetPos(player.GetPos() + player.GetDir() * player.GetVelocity() * frame_time);
	}
	else {
		player.SetPos(player.GetPos() + player.GetDir() * (sqrt(2) / 2) * player.GetVelocity() * frame_time);
	}
}

void RunState::enter(Player& player)
{
	player.SetImage(STATE_RUN);
}

void RunState::exit(Player& player)
{
	player.DestroyImage();
}
