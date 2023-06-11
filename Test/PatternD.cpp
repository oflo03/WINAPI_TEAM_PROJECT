#include "PatternD.h"
#include "PatternA.h"
#include"BossIdle.h"
#include"Bullet.h"
#include"EffectManager.h"

extern HDC mDC;
extern double frame_time;

void PatternD::enter(Boss& boss)
{
	boss.handType[LEFT] = 1;
	boss.handType[RIGHT] = 2;
	boss.frame = 3;
}

BossState* PatternD::handle_event(Boss& boss)
{
	if ((int)time == 600) {
		return new BossIdle();
	}
	else if ((int)time >= 50 && (int)time < 550) {
		if ((int)attackCoolTime==0&&!isAttack) {
			warning=new Effect(CEffect::PATTERND, Vector2D<float>(boss.target->GetPos().x, boss.target->GetPos().y+22 - Effect::effect[CEffect::PATTERND].size.bottom));
			EffectManager::getInstance()->set_effect(warning);
			isAttack = true;
		}
		else if ((int)attackCoolTime == 6) {
			EffectManager::getInstance()->set_effect(new Effect(CEffect::PATTERNB, Vector2D<float>(boss.target->GetPos().x, boss.target->GetPos().y+22- Effect::effect[CEffect::PATTERNB].size.bottom)));
			isAttack = false;
			RECT t;
			RECT r = { pos.x - Effect::effect[CEffect::PATTERNB].size.right,pos.y-5,pos.x + Effect::effect[CEffect::PATTERNB].size.right,pos.y + 20 };
			for (auto& other : COLL) {
				for (int i = 0; i < 4; i++) {
					if (other->layer == player) {
						RECT rect = { other->pos.x - other->size.x, other->pos.y - other->size.y ,other->pos.x + other->size.x, other->pos.y + other->size.y };
						if (IntersectRect(&t,&rect,&r)) {
							other->owner->handle_collision(enemyBullet, 1);
							break;
						}
					}
				}
			}
		}
	}
	return nullptr;
}

void PatternD::update(Boss& boss)
{
	if ((int)time < 50) {
		boss.handPos[0].x += 1;
		boss.handPos[1].x -= 1;
	}
	else if ((int)time >= 50 && (int)time < 550) {
		if ((int)attackCoolTime >= 0&&(int)attackCoolTime < 4) {
			warning->pos= Vector2D<float>(boss.target->GetPos().x, boss.target->GetPos().y+22 - Effect::effect[CEffect::PATTERND].size.bottom);
			attackCoolTime = (attackCoolTime + frame_time * 2 * 6);
			pos = boss.target->GetPos();
		}
		else if((int)attackCoolTime == 6)
			attackCoolTime = -10;
		else if ((int)attackCoolTime <0|| (int)attackCoolTime >=4&& (int)attackCoolTime <6)
			attackCoolTime = (attackCoolTime + frame_time * 2 * 6);
	}
	else if ((int)time >= 550) {
		boss.handPos[0].x -= 1;
		boss.handPos[1].x += 1;
	}
	time++;
}
