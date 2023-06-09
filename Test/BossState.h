#pragma once
#include"Boss.h"

class Boss;

class BossState
{
protected:
public:
	virtual void enter(Boss& boss) = 0;
	virtual BossState* handle_event(Boss& boss) = 0;
	virtual void update(Boss& boss) = 0;
};

