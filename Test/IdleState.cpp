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
		player.set_horizon() = 1;
		dirX = 1;
		isMove = true;
	}
	else if (GetAsyncKeyState('A')) {
		player.set_horizon() = -1;
		dirX = -1;
		isMove = true;
	}
	if (GetAsyncKeyState('W')) {
		player.set_virtical() = false;
		dirY = -1;
		if (!GetAsyncKeyState('A') && !GetAsyncKeyState('D'))
			player.set_horizon() = 0;
		isMove = true;
	}
	else if (GetAsyncKeyState('S')) {
		player.set_virtical() = true;
		dirY = 1;
		if (!GetAsyncKeyState('A') && !GetAsyncKeyState('D'))
			player.set_horizon() = 0;
		isMove = true;
	}
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
