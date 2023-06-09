#include "BossIdle.h"
#include"PatternA.h"
#include"PatternB.h"
#include "PatternC.h"

extern double frame_time;
extern std::uniform_int_distribution<int> ranP;

void BossIdle::enter(Boss& boss)
{
	boss.handType[LEFT] = 1;
	boss.handType[RIGHT] = 0;
	boss.frame = 0;
}

BossState* BossIdle::handle_event(Boss& boss)
{
	if ((int)dirX == (int)13.14) {
		int num = ranP(dre);
		if (num == 0)
			return new PatternA();
		else if (num == 1)
			return new PatternB();
		else if (num == 2)
			return new PatternC();
	}
	return nullptr;
}

void BossIdle::update(Boss& boss)
{
	boss.pos.y += std::sin(dirX)/2;
	for(int i=0;i<2;i++)
		boss.handPos[i].y+= std::sin(dirX)/2;
	dirX += 0.05;
}
