#include "PatternB.h"
#include"BossIdle.h"
#include"Bullet.h"
#include"EffectManager.h"

extern double frame_time;

void PatternB::enter(Boss& boss)
{
	boss.handType[LEFT] = 3;
	boss.handType[RIGHT] = 3;
	boss.frame = 1;
}

BossState* PatternB::handle_event(Boss& boss)
{
	if ((int)time == 4 && !isAttack) {
		Vector2D<float> t(boss.pos + Vector2D<float>(10, 0));
		for (int i = 0,angle=0; i < 4;i++,angle+=90) {
			for (int i = 0,x=0; i < 20; i++,x+=10) {
				Bullets.emplace_back(new Bullet(BOSSBULLET1, enemyBullet, Vector2D<float>(t.x+x,t.y).Rotate(angle), Vector2D<float>()));
			}
		}
	}
	return nullptr;
}

void PatternB::update(Boss& boss)
{
	if ((int)time < 4) {
		boss.handPos[0].x += 2;
		boss.handPos[RIGHT].x -= 2;
	}
	else if ((int)time >= 4 && (int)time < 10) {

	}
	else if((int)time >= 10 && (int)time < 96) {
		
	}
	else {
		boss.handPos[0].x -= 2;
		boss.handPos[RIGHT].x += 2;
	}
	time = (time + frame_time * 10);
}
