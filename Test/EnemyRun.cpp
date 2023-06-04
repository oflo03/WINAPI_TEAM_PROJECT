#include "EnemyRun.h"
#include"EnemyIdle.h"

extern double frame_time;

void EnemyRun::enter(Enemy& player)
{
	player.SetImage(STATE_RUN);
}

void EnemyRun::exit(Enemy& player)
{
	player.DestroyImage();
}

EnemyState* EnemyRun::handle_event(Enemy& player)
{
	player.SetDir((player.target->GetPos() - player.GetPos()).Normalize());
	if (player.attackable())
		return new EnemyIdle();
	else
		return nullptr;
}

void EnemyRun::update(Enemy& player)
{
	player.SetPos(player.GetPos() + player.GetDir() * player.GetVelocity() * frame_time);
	player.SetDirection();
}
