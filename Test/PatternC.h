#pragma once
#include "BossState.h"
class PatternC :
    public BossState
{
private:
	float time;
	float attackCoolTime;
	bool isLeft;
public:
	PatternC() { time = 0, attackCoolTime = 0, isLeft = true; }
	virtual void enter(Boss& boss);
	virtual BossState* handle_event(Boss& boss);
	virtual void update(Boss& boss);
};

