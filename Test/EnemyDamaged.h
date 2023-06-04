#pragma once
#include "EnemyState.h"
class EnemyDamaged :
    public EnemyState
{
private:
	float time;
public:
	EnemyDamaged() { time = 0.01; }
	virtual void enter(Enemy& player);
	virtual void exit(Enemy& player);
	virtual EnemyState* handle_event(Enemy& player);
	virtual void update(Enemy& player);
};

