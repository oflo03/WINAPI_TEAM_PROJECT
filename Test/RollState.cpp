#include "RollState.h"
#include"IdleState.h"
#include"RunState.h"
#include"SoundManager.h"

extern double frame_time;

RollState::~RollState()
{
}

PlayerState* RollState::handle_event(Player& player)
{
	if ((int)rollingTime == 9)
	{
		player.col->layer = 1;
		return new IdleState;
	}
	return nullptr;
}

void RollState::update(Player& player)
{
	player.col->layer = rolled_player;
	rollingTime = (rollingTime + frame_time * 2 * 9);
	if ((int)rollingTime >= 6) return;
	if(dir.GetLenth()==1){
		player.SetPos(player.GetPos() + dir * player.GetVelocity()*3 * frame_time);
	}
	else {
		player.SetPos(player.GetPos() + dir * (sqrt(2) / 2) * player.GetVelocity()*3 * frame_time);
	}
}

void RollState::enter(Player& player)
{
	player.SetCurState(STATE_ROLL);
	SoundManager::getInstance()->play(ROLLING);
}


bool Player::GetIfRoll() { return curstate==STATE_ROLL; };