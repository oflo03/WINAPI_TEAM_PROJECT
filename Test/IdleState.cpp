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
	player.SetDirection();
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
