#pragma once
#include "EnemyState.h"
class EnemyRun :
    public EnemyState
{
	virtual void enter(Enemy& player);
	virtual void exit(Enemy& player);
	virtual EnemyState* handle_event(Enemy& player);
	virtual void update(Enemy& player);
};

