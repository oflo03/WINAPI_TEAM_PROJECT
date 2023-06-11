#include"EnemyManager.h"
#include "Bat.h"
#include"EffectManager.h"

Animation Bat::animation[2];

enum BATSTATE {
	IDLE, DEAD
};

extern double frame_time;

void Bat::init()
{
	animation[IDLE].resource.Load(L"resources/bat.png");
	animation[IDLE].frame = 6;
	animation[IDLE].size = { 0,0,animation[IDLE].resource.GetWidth() / animation[IDLE].frame,animation[IDLE].resource.GetHeight() };
	animation[IDLE].velocity = 2;
	animation[DEAD].resource.Load(L"resources/bat_damaged.png");
	animation[DEAD].frame = 4;
	animation[DEAD].size = { 0,0,animation[DEAD].resource.GetWidth() / animation[DEAD].frame,animation[DEAD].resource.GetHeight() };
	animation[DEAD].velocity = 2;
}

void Bat::release()
{
	for (int i = 0; i < 2; i++) {
		animation[i].resource.Destroy();
	}
}

Bat::Bat(double x, double y, Player* target) : Enemy(x, y)
{
	shadow.Load(L"resources/shadow.png");
	velocity = 200;
	state = IDLE;
	attackRange = 600;
	lastPos = pos;
}



Bat::~Bat()
{
	shadow.Destroy();
}


void Bat::draw_character(HDC mDC)
{
	if (col || state == DEAD) {
		float yDest = pos.y - animation[IDLE].size.bottom;
		shadow.Draw(mDC, pos.x - shadow.GetWidth(), pos.y + 60 - 2 - shadow.GetHeight(), shadow.GetWidth() * 2, shadow.GetHeight() * 2);
		animation[state].resource.Draw(mDC, pos.x - animation[state].size.right, yDest - 20, animation[state].size.right * 2, animation[state].size.bottom * 2,
			(int)frame * animation[state].size.right, 0, animation[state].size.right, animation[state].size.bottom);
	}
	else
		spawnAnim.resource.Draw(mDC, pos.x - spawnAnim.size.right, pos.y - spawnAnim.size.bottom, spawnAnim.size.right * 2, spawnAnim.size.bottom * 2,
			(int)frame * spawnAnim.size.right, 0, spawnAnim.size.right, spawnAnim.size.bottom);
}

void Bat::handle_event()
{
	if (col) {
		if (attackable())
			targetLocked = true;
		if (targetLocked)
			dir = (target->GetPos() - pos).Normalize();
		else
			dir.x = dir.y = 0;
	}
}

void Bat::update()
{
	if (col || state == DEAD) {
		lastPos = pos;
		frame = (frame + frame_time * animation[state].velocity * animation[state].frame);
		if (state == IDLE) {
			pos = pos + dir * velocity * frame_time;
			if (frame >= animation[state].frame) frame = 0;
			col->pos = pos;
		}
		else {
			if ((int)frame == animation[state].frame) {
				EnemyManager::getInstance()->delete_enemy(this);
				deleteSet.insert(this);
				EffectManager::getInstance()->set_effect(new Effect(CEffect::BATDIE, pos));
				for (auto& other : COLL) {
					for (int i = 0; i < 4; i++) {
						if (other->layer == player) {
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
	else {
		frame = (frame + frame_time * spawnAnim.velocity * spawnAnim.frame);
		if ((int)frame == spawnAnim.frame) {
			col = new Collider(10);
			col->owner = this;
			col->layer = enemy;
			col->pos = pos;
			col->damage = 5;
			COLL.emplace_back(col);
			frame = 0;
		}
	}
}

void Bat::SetDirection()
{
}

void Bat::attack()
{

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
		state = DEAD;
		for (auto i = COLL.begin(); i != COLL.end(); ++i)
			if (COLL[i - COLL.begin()] == this->col)
			{
				COLL.erase(i);
				break;
			}
		delete this->col;
		this->col = nullptr;
		frame = 0;
		break;
	default:
		break;
	}
}
