#include "DieState.h"
#include"EffectManager.h"

void DieState::enter(Boss& boss)
{
	boss.frame = 4;
	boss.handType[LEFT] = 4;
	boss.handType[RIGHT] = 4;
}

BossState* DieState::handle_event(Boss& boss)
{
	if ((int)dirX == (int)13.14) {
		EffectManager::getInstance()->set_effect(new Effect(TELEPORT, boss.pos));
	}
	return nullptr;
}

void DieState::update(Boss& boss)
{
	boss.pos.y += std::sin(dirX) / 2;
	for (int i = 0; i < 2; i++)
		boss.handPos[i].y += std::sin(dirX) / 2;
	dirX += 0.05;
}
