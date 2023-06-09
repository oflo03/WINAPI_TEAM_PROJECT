#pragma once
#include "BossState.h"
class PatternB :
    public BossState
{
private:
	float time;
	bool isAttack;
public:
	PatternB() { time = 0, isAttack = false; }
	virtual void enter(Boss& boss);
	virtual BossState* handle_event(Boss& boss);
	virtual void update(Boss& boss);
};

