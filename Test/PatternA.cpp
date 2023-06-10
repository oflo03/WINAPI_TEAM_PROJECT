#include "PatternA.h"
#include"BossIdle.h"
#include"Bullet.h"
#include"EffectManager.h"

extern double frame_time;

void PatternA::enter(Boss& boss)
{
	boss.handType[LEFT] = 0;
	boss.handType[RIGHT] = 1;
	boss.frame = 2;
}

BossState* PatternA::handle_event(Boss& boss)
{
	if ((int)time == 1000) {
		return new BossIdle();
	}
	else if ((int)time >= 50 && (int)time < 950) {
		if((int)attackCoolTime==0){
			EffectManager::getInstance()->set_effect(new Effect(CEffect::PATTERNA, Vector2D<float>(boss.handPos[0].x, boss.handPos[0].y - 40)));
		}
		else if((int)attackCoolTime==8){
			Vector2D<float> t(boss.target->GetPos() - Vector2D<float>(boss.handPos[0].x, boss.handPos[0].y - 40));
			t.Normalize();
			Bullets.emplace_back(new Bullet(BOSSBULLET2, enemyBullet, Vector2D<float>(boss.handPos[0].x, boss.handPos[0].y - 40) + (t * 5), t * 10));
		}
	}
	return nullptr;
}

void PatternA::update(Boss& boss)
{
	if ((int)time <50)
		boss.handPos[0].y -= 2;
	else if((int)time >= 50&& (int)time<950){
		if ((int)attackCoolTime < 8)
			attackCoolTime = (attackCoolTime + frame_time * 3 * 8);
		else
			attackCoolTime = -5;
	}
	else if((int)time >= 950){
		boss.handPos[0].y += 2;
	}
	time ++;
}
