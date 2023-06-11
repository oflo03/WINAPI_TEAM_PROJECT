#include "DeadState.h"
#include"SoundManager.h"

DeadState::~DeadState()
{

}

PlayerState* DeadState::handle_event(Player& player)
{
	return nullptr;
}

void DeadState::update(Player& player)
{
}

void DeadState::enter(Player& player)
{
	SoundManager::getInstance()->stop(SOUND::MainState);
	SoundManager::getInstance()->play(SOUND::GAME_OVER);
	player.SetCurState(STATE_DEAD);
}
