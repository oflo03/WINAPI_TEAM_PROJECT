#include "BossIdle.h"
#include"PatternA.h"

extern double frame_time;


void BossIdle::enter(Boss& boss)
{
	boss.handType[LEFT] = 1;
	boss.handType[RIGHT] = 0;
}

BossState* BossIdle::handle_event(Boss& boss)
{
	if ((int)dirX == (int)13.14) {
		return new PatternA();
	}
	return nullptr;
}

void BossIdle::update(Boss& boss)
{
	boss.pos.y += std::sin(dirX)/2;
	for(int i=0;i<2;i++)
		boss.handPos[i].y+= std::sin(dirX)/2;
	dirX += 0.1;
}
