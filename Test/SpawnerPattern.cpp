#include "SpawnerPattern.h"
#include "BossIdle.h"
#include"EnemyManager.h"

extern double frame_time;
extern std::random_device rd;

void SpawnerPattern::enter(Boss& boss)
{
	boss.handType[LEFT] = 1;
	boss.handType[RIGHT] = 0;
	boss.frame = 3;
}

BossState* SpawnerPattern::handle_event(Boss& boss)
{
	if (time == 600) {
		boss.pattern.push_back(3);
		boss.pattern.push_back(2);
		boss.pattern.push_back(1);
		boss.pattern.push_back(0);
		std::shuffle(boss.pattern.begin(), boss.pattern.end(), rd);
		return new BossIdle();
	}
	if (time==50) {
		EnemyManager* spawner = EnemyManager::getInstance();
		spawner->spawn(PISTOLMAN, 260, 310);
		spawner->spawn(RIFLEMAN, 1700, 310);
		spawner->spawn(SHOTGUNMAN, 260, 780);
		spawner->spawn(BOMBSHE, 950, 880);
		spawner->spawn(BAT, 1400, 780);
	}
	return nullptr;
}

void SpawnerPattern::update(Boss& boss)
{
	time++;
}
