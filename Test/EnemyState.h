#pragma once
#include"Enemy.h"
#include"Weapon.h"

class Enemy;

class EnemyState {
private:
public:
	virtual void enter(Enemy& player) = 0;
	virtual void exit(Enemy& player) = 0;
	virtual EnemyState* handle_event(Enemy& player) = 0;
	virtual void update(Enemy& player) = 0;
};
