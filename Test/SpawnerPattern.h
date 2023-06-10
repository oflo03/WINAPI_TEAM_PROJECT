#pragma once
#include "BossState.h"
class SpawnerPattern :
    public BossState
{
private:
	int time;
	float attackCoolTime;
	Vector2D<float> pos;
public:
	SpawnerPattern() {
		time = 0, attackCoolTime = 0;
	}
	void enter(Boss& boss);
	virtual BossState* handle_event(Boss& boss);
	virtual void update(Boss& boss);
};

