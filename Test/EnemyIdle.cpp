#include "EnemyIdle.h"
#include"EnemyRun.h"

void EnemyIdle::enter(Enemy& player)
{
	player.SetImage(STATE_IDLE);
}

void EnemyIdle::exit(Enemy& player)
{
	player.DestroyImage();
}

EnemyState* EnemyIdle::handle_event(Enemy& player)
{
	player.SetDir((player.target->GetPos() - player.GetPos()).Normalize());
	if (player.attackable()) {
		player.attack();
		return nullptr;
	}
	else {
		return new EnemyRun();
	}
}

void EnemyIdle::update(Enemy& player)
{
	player.SetDirection();
}
