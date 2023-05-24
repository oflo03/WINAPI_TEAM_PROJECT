#include "IdleState.h"
#include"RunState.h"
#include"RollState.h"

IdleState::~IdleState()
{
}

PlayerState* IdleState::handle_event(Player& player)
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
	if (GetAsyncKeyState('W')) {
		player.set_virtical() = false;
		player.SetDirY(-1);
		if (!GetAsyncKeyState('A') && !GetAsyncKeyState('D'))
			player.set_horizon() = 0;
		isMove = true;
	}
	else if (GetAsyncKeyState('S')) {
		player.set_virtical() = true;
		player.SetDirY(1);
		if (!GetAsyncKeyState('A') && !GetAsyncKeyState('D'))
			player.set_horizon() = 0;
		isMove = true;
	}
	if (GetAsyncKeyState(VK_RBUTTON)& 0x8000) {
		int x, y;
		switch (player.GetDirection())
		{
		case FRONT:
			x = 0, y = 1;
			break;
		case FRONT_RIGHT:
		case BACK_RIGHT:
			x = 1; y = 0;
			break;
		case FRONT_LEFT:
		case BACK_LEFT:
			x = -1; y = 0;
			break;
		case BACK:
			x = 0, y = -1;
			break;
		default:
			break;
		}
		return new RollState(x,y);
	}
	if (isMove) {
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
