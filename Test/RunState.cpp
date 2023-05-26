#include "RunState.h"
#include"IdleState.h"
#include"RollState.h"

RunState::~RunState()
{
}

PlayerState* RunState::handle_event(Player& player)
{
	float dirX=0, dirY = 0;
	bool isMove = false;
	if (GetAsyncKeyState('D')) {
		player.set_horizon() = 1;
		dirX = 1;
		isMove = true;
	}
	else if (GetAsyncKeyState('A')) {
		player.set_horizon() = -1;
		dirX = -1;
		isMove = true;
	}
	else dirX = 0;
	if (GetAsyncKeyState('W')) {
		dirY = -1;
		player.set_virtical() = false;
		if (!GetAsyncKeyState('A') && !GetAsyncKeyState('D'))
			player.set_horizon() = 0;
		isMove = true;
	}
	else if (GetAsyncKeyState('S')) {
		dirY = 1;
		if (!GetAsyncKeyState('A') && !GetAsyncKeyState('D'))
			player.set_horizon() = 0;
		player.set_virtical() = true;
		isMove = true;
	}
	else dirY = 0;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
		player.SetDir(Vector2D<float>(0,0));
		return new RollState(dirX,dirY);
	}
	if (isMove) {
		player.SetDir(Vector2D<float>(dirX, dirY));
		return nullptr;
	}
	return new IdleState();
}

void RunState::update(Player& player)
{
	player.SetPos(player.GetPos() + player.GetDir() * player.GetVelocity() * 0.01f);
}

void RunState::enter(Player& player)
{
	player.SetImage(STATE_RUN);
}

void RunState::exit(Player& player)
{
	player.DestroyImage();
}
