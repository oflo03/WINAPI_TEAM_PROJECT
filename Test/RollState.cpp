#include "RollState.h"
#include"IdleState.h"
#include"RunState.h"

extern double frame_time;

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
		player.SetPos(player.GetPos() + dir * player.GetVelocity()*3 * frame_time);
	}
	else {
		player.SetPos(player.GetPos() + dir * (sqrt(2) / 2) * player.GetVelocity()*3 * frame_time);
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



bool Player::GetIfRoll() { return (dynamic_cast<RollState*>(state) != nullptr); };