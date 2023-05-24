#include "RunState.h"
#include"IdleState.h"
#include"RollState.h"

RunState::~RunState()
{
}

PlayerState* RunState::handle_event(Player& player)
{
	bool isMove = false;
	if (GetAsyncKeyState('D')) {
		player.set_horizon() = 1;
		player.SetDirX(1);
		isMove = true;
	}
	else if (GetAsyncKeyState('A')) {
		player.set_horizon() = -1;
		player.SetDirX(-1);
		isMove = true;
	}
	else player.SetDirX(0);
	if (GetAsyncKeyState('W')) {
		player.SetDirY(-1);
		player.set_virtical() = false;
		if (!GetAsyncKeyState('A') && !GetAsyncKeyState('D'))
			player.set_horizon() = 0;
		isMove = true;
	}
	else if (GetAsyncKeyState('S')) {
		player.SetDirY(1);
		if (!GetAsyncKeyState('A') && !GetAsyncKeyState('D'))
			player.set_horizon() = 0;
		player.set_virtical() = true;
		isMove = true;
	}
	else player.SetDirY(0);
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
		int x = player.GetDirX();
		int y = player.GetDirY();
		player.SetDirX(0);
		player.SetDirY(0);
		return new RollState(x,y);
	}
	if (isMove)
		return nullptr;
	return new IdleState();
}

void RunState::update(Player& player)
{
	player.SetX(player.GetX() + player.GetDirX() * player.GetVelocity() * 0.01);
	player.SetY(player.GetY() + player.GetDirY() * player.GetVelocity() * 0.01);
}

void RunState::enter(Player& player)
{
	player.SetImage(STATE_RUN);
}

void RunState::exit(Player& player)
{
	player.DestroyImage();
}
