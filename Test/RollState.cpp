#include "RollState.h"
#include"IdleState.h"
#include"RunState.h"

RollState::~RollState()
{
}

PlayerState* RollState::handle_event(Player& player)
{
	if (rollingTime == 60)
		return new IdleState;
	else if(rollingTime>40){
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
		if (isMove) {
			return new RunState();
		}
	}
	return nullptr;
}

void RollState::update(Player& player)
{
	rollingTime++;
	if (rollingTime > 35) return;
	if(dirX!=0&&dirY!=0){
		player.SetX(player.GetX() + dirX * player.GetVelocity() * 0.015);
		player.SetY(player.GetY() + dirY * player.GetVelocity() * 0.015);
	}
	else {
		player.SetX(player.GetX() + dirX * player.GetVelocity() * 0.02);
		player.SetY(player.GetY() + dirY * player.GetVelocity() * 0.02);
	}
}

void RollState::enter(Player& player)
{
	player.SetImage(STATE_ROLL);
}

void RollState::exit(Player& player)
{
	player.DestroyImage();
}
