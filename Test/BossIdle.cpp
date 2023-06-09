#include "BossIdle.h"

extern double frame_time;


void BossIdle::enter(Boss& boss)
{

}

BossState* BossIdle::handle_event(Boss& boss)
{
	if ((int)dirX == (int)6.14) {

	}
	return nullptr;
}

void BossIdle::update(Boss& boss)
{
	boss.pos.y += std::sin(dirX);
	for(int i=0;i<2;i++)
		boss.handPos[i].y+= std::sin(dirX)/4;
	dirX += 0.1;
}
