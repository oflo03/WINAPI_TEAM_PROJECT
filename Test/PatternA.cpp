#include "PatternA.h"
#include"BossIdle.h"
#include"Bullet.h"
#include"EffectManager.h"

extern double frame_time;

void PatternA::enter(Boss& boss)
{
	boss.leftHand = 0;
	boss.rightHand = 1;
}

BossState* PatternA::handle_event(Boss& boss)
{
	if ((int)time == 10) {
		return new BossIdle();
	}
	else if ((int)time >= 2) {
		if((int)attackCoolTime==0){
			EffectManager::getInstance()->set_effect(new Effect(CEffect::PATTERNA, Vector2D<float>(boss.handPos[0].x + 5, boss.handPos[0].y - 10)));
		}
		else if((int)attackCoolTime==4){
			Vector2D<float> t(boss.target->GetPos() - Vector2D<float>(boss.handPos[0].x + 5, boss.handPos[0].y - 10));
			t.Normalize();
			Bullets.emplace_back(new Bullet(BOSSBULLET1, enemyBullet,Vector2D<float>(boss.handPos[0].x, boss.handPos[0].y-20), t*10));
		}
	}
}

void PatternA::update(Boss& boss)
{
	time = (time + frame_time * 10);
	if ((int)time < 2)
		boss.handPos[0].y += 2;
	else {
		if ((int)attackCoolTime < 4)
			attackCoolTime = (attackCoolTime * frame_time * 3 * 4);
		else
			attackCoolTime = 0;
	}
}
