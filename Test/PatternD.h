#pragma once
#include "BossState.h"
#include"Effect.h"

class PatternD :
    public BossState
{
private:
	float time;
	float attackCoolTime;
	Effect* warning;
	bool isAttack;
	Vector2D<float> pos;
public:
	PatternD() {
		time = 0, attackCoolTime = 0;
		isAttack = false;
		warning = nullptr;
	}
	void enter(Boss& boss);
	virtual BossState* handle_event(Boss& boss);
	virtual void update(Boss& boss);
};

