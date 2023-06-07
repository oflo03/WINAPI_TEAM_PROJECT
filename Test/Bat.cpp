#include"EnemyManager.h"
#include "Bat.h"
#include"EffectManager.h"

extern double frame_time;

Bat::Bat(double x, double y, Player* target) : Enemy(x, y)
{
	SetImage(STATE_IDLE);
	shadow.Load(L"shadow.png");
	velocity = 200;
	state = STATE_IDLE;
	attackRange = 400;
	col = new Collider(6);
	col->owner = this;
	col->layer = 3;
	col->pos = pos;
	col->damage = 5;
	COLL.emplace_back(col);
}



Bat::~Bat()
{
	DestroyImage();
	shadow.Destroy();
}

void Bat::draw_character(HDC mDC)
{
	float yDest = pos.y - (animation.size.bottom) * 2;
	shadow.Draw(mDC, pos.x - shadow.GetWidth(), pos.y + col->size.y*2 - 2 - shadow.GetHeight(), shadow.GetWidth() * 2, shadow.GetHeight() * 2);
	animation.resource.Draw(mDC, pos.x - animation.size.right, yDest - 20, animation.size.right * 2, animation.size.bottom * 2,
		(int)frame * animation.size.right, 0, animation.size.right, animation.size.bottom
	);
}

void Bat::handle_event()
{
	if (attackable())
		targetLocked = true;
	if (targetLocked)
		dir = (target->GetPos() - pos).Normalize();
	else
		dir.x = dir.y = 0;
}

void Bat::update()
{
	lastPos = pos;
	frame = (frame + frame_time * 5 * animation.frame);
	if (frame >= animation.frame) frame = 0;
	col->pos = pos;
}

void Bat::SetImage(int state)
{
	switch (state)
	{
	case STATE_IDLE:
		animation.resource.Load(L"bat.png");
		animation.frame = 6;
		animation.size = { 0,0,animation.resource.GetWidth() / animation.frame,animation.resource.GetHeight() };
		break;
	case STATE_RUN:
		animation.resource.Load(L"bat.png");
		animation.frame = 6;
		animation.size = { 0,0,animation.resource.GetWidth() / animation.frame,animation.resource.GetHeight() };
		break;
	default:
		break;
	}
}

void Bat::attack()
{

}

void Bat::DestroyImage()
{
	animation.resource.Destroy();
}

void Bat::handle_collision(int otherLayer, int damage)
{
	switch (otherLayer)
	{
	case wall:
		if (!isWallCollision(Vector2D<float>(pos.x + velocity * frame_time / 2 * (pos.x > lastPos.x ? 1 : -1), lastPos.y), col->size))
		{
			pos.x += velocity * frame_time / 2 * (pos.x > lastPos.x ? 1 : -1);
			pos.y = lastPos.y;
		}
		else if (!isWallCollision(Vector2D<float>(lastPos.x, pos.y + velocity * frame_time / 2 * (pos.x > lastPos.x ? 1 : -1)), col->size))
		{
			pos.x = lastPos.x;
			pos.y += velocity * frame_time / 2 * (pos.y > lastPos.y ? 1 : -1);
		}
		else
			pos = lastPos;
		lastPos = pos;
		col->pos = pos;
		break;
	case player:
	case rolled_player:
	case playerMelee:
	case playerBullet:
		EffectManager::getInstance()->set_effect(new DieMotion(BAT, L"bat_damaged.png", col->pos, 4, 3));
		EnemyManager::getInstance()->delete_enemy(this);
		deleteSet.insert(this);
		break;
	default:
		break;
	}
}
