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
	}
	return nullptr;
}

void RollState::update(Player& player)
{
	rollingTime++;
	if (rollingTime > 35) return;
	if(dir.GetLenth()==1){
		player.SetPos(player.GetPos() + dir * player.GetVelocity() * 0.02f);
	}
	else {
		player.SetPos(player.GetPos() + dir * player.GetVelocity() * 0.015f);
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
