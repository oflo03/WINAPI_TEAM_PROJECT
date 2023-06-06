#include "EnemyDamaged.h"
#include"EnemyIdle.h"

extern double frame_time;

void EnemyDamaged::enter(Enemy& player)
{
	player.SetImage(STATE_DAMAGED);
}

void EnemyDamaged::exit(Enemy& player)
{
	player.DestroyImage();
}

EnemyState* EnemyDamaged::handle_event(Enemy& player)
{
	if (time >= 5)
	{
		player.col->layer = enemy;
		return new EnemyIdle();
	}
	return nullptr;
}

void EnemyDamaged::update(Enemy& player)
{
	time = (time + frame_time * 10 * 2);
}