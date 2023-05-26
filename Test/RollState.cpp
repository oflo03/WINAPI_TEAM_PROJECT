#include "RollState.h"
#include"IdleState.h"
#include"RunState.h"

RollState::~RollState()
{
}

PlayerState* RollState::handle_event(Player& player)
{
	if (rollingTime == 31)
		return new IdleState;
	return nullptr;
}

void RollState::update(Player& player)
{
	rollingTime++;
	if (rollingTime > 25) return;
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
