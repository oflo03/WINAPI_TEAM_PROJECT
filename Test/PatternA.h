#pragma once
#include "BossState.h"
class PatternA :
    public BossState
{
private:
	float time;
	float attackCoolTime;
public:
	PatternA() { time = 0, attackCoolTime=0; }
	virtual void enter(Boss& boss);
	virtual BossState* handle_event(Boss& boss);
	virtual void update(Boss& boss);
};

