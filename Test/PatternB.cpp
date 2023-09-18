#include "PatternB.h"
#include"BossIdle.h"
#include"Bullet.h"
#include"EffectManager.h"
#include"DieState.h"

extern double frame_time;

void PatternB::enter(Boss& boss)
{
	boss.handType[LEFT] = 3;
	boss.handType[RIGHT] = 3;
	boss.frame = 1;
}

BossState* PatternB::handle_event(Boss& boss)
{
	if ((int)time == 10 && !isAttack) {
		Vector2D<float> t(10,0);
		Vector2D<float> p = boss.pos;
		for (int i = 0, angle = 0; i < 4; i++, angle += 90) {
			for (int j = 0, x = 0; j < 40; j++, x += 30) {
				Bullets.emplace_back(new Bullet(BOSSBULLET1, enemyBullet, Vector2D<float>(t.x + x, t.y).Rotate(angle)+p, boss.pos));
			}
		}
		isAttack = true;
	}
	else if ((int)time == 130) {
		return new BossIdle();
	}
	if (boss.getHP() <= 0)
		return new DieState;
	return nullptr;
}

void PatternB::update(Boss& boss)
{
	if ((int)time < 4) {
		boss.handPos[0].x += 1;
		boss.handPos[RIGHT].x -= 1;
	}
	else if ((int)time >= 4 && (int)time < 10) {

	}
	else if((int)time >= 10 && (int)time < 126) {
		
	}
	else {
		boss.handPos[0].x -= 1;
		boss.handPos[RIGHT].x += 1;
	}
	time = (time + frame_time * 10);
}
