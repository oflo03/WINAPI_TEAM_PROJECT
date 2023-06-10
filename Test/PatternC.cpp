#include "PatternC.h"
#include "PatternA.h"
#include"BossIdle.h"
#include"Bullet.h"
#include"EffectManager.h"

extern double frame_time;

void PatternC::enter(Boss& boss)
{
	boss.handType[LEFT] = 2;
	boss.handType[RIGHT] = 2;
	boss.frame = 0;
}

BossState* PatternC::handle_event(Boss& boss)
{
	if ((int)time == 1000) {
		return new BossIdle();
	}
	else if ((int)time >= 50 && (int)time < 950) {
		if ((int)attackCoolTime == 0) {
			EffectManager::getInstance()->set_effect(new Effect(CEffect::PATTERNC, Vector2D<float>(boss.handPos[isLeft].x, boss.handPos[isLeft].y)));
		}
		else if ((int)attackCoolTime == 9) {
			Vector2D<float> p = boss.handPos[isLeft];
			Vector2D<float> t(2, 0);
			for (int i = 0; i < 40; i++) {
				Bullets.emplace_back(new Bullet(BOSSBULLET3, enemyBullet, t.Rotate(9) + p, t*2));
			}
			isLeft = !isLeft;
		}
	}
	return nullptr;
}

void PatternC::update(Boss& boss)
{
	if ((int)time < 50) {
		boss.handPos[0]+=Vector2D<float>(-1,-2);
		boss.handPos[1] += Vector2D<float>(+2, 1);
	}
	else if ((int)time >=50 && (int)time < 950) {
		if ((int)attackCoolTime < 9)
			attackCoolTime = (attackCoolTime + frame_time * 2 * 9);
		else
			attackCoolTime = -10;
	}
	else if ((int)time >= 950) {
		boss.handPos[0] += Vector2D<float>(1, 2);
		boss.handPos[1] += Vector2D<float>(-2, -1);
	}
	time++;
}
