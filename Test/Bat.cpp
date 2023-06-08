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
	attackRange = 600;
	col = new Collider(10);
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
	float yDest = pos.y-10;
	shadow.Draw(mDC, pos.x - shadow.GetWidth(), pos.y + 60 - 2 - shadow.GetHeight(), shadow.GetWidth() * 2, shadow.GetHeight() * 2);
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
	if(state==STATE_IDLE){
		pos = pos + dir * velocity * frame_time;
		frame = (frame + frame_time * 2 * animation.frame);
		if (frame >= animation.frame) frame = 0;
		col->pos = pos;
	}
	else {
		if((int)frame< animation.frame)
			frame = (frame + frame_time * 2 * animation.frame);
		else {
			EnemyManager::getInstance()->delete_enemy(this);
			deleteSet.insert(this);
			EffectManager::getInstance()->set_effect(new Effect(L"bat_explosion.png", pos, 3, 5));
			for (auto& other : COLL) {
				for (int i = 0; i < 4; i++) {
					if (other->layer==player) {
						Vector2D<float> dot[4] = { Vector2D<float>(other->pos.x - other->size.x, other->pos.y - other->size.y),
						Vector2D<float>(other->pos.x + other->size.x, other->pos.y - other->size.y),
						Vector2D<float>(other->pos.x + other->size.x, other->pos.y + other->size.y),
						Vector2D<float>(other->pos.x - other->size.x, other->pos.y + other->size.y) };
						if ((dot[i] - pos).GetLenth() <= 60) {
							other->owner->handle_collision(enemyBullet, 2);
							break;
						}
					}
					else if (other->layer == enemy) {
						Vector2D<float> dot[4] = { Vector2D<float>(other->pos.x - other->size.x, other->pos.y - other->size.y),
						Vector2D<float>(other->pos.x + other->size.x, other->pos.y - other->size.y),
						Vector2D<float>(other->pos.x + other->size.x, other->pos.y + other->size.y),
						Vector2D<float>(other->pos.x - other->size.x, other->pos.y + other->size.y) };
						if ((dot[i] - pos).GetLenth() <= 60) {
							other->owner->handle_collision(playerBullet, 10);
							break;
						}
					}
				}
			}
		}
	}
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
	case STATE_DEAD:
		animation.resource.Load(L"bat_damaged.png");
		animation.frame = 4;
		animation.size = { 0,0,animation.resource.GetWidth() / animation.frame,animation.resource.GetHeight() };
		break;
	default:
		break;
	}
}

void Bat::SetDirection()
{
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
	case playerMelee:
	case playerBullet:
		state = STATE_DEAD;
		for (auto i = COLL.begin(); i != COLL.end(); ++i)
			if (COLL[i - COLL.begin()] == this->col)
			{
				COLL.erase(i);
				break;
			}
		delete this->col;
		this->col = nullptr;
		DestroyImage();
		SetImage(state);
		frame = 0;
		break;
	default:
		break;
	}
}
