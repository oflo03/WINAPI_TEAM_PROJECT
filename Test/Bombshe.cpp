#include "Bombshe.h"
#include"EnemyManager.h"

extern double frame_time;
extern bool lookRange;
extern HPEN GREENP;

Bombshe::Bombshe(double x, double y, Player* target) : Enemy(x, y),isAttack(false)
{
	SetImage(STATE_IDLE);
	shadow.Load(L"shadow.png");
	attackSize = 0;
	velocity = 100;
	moveTime = 200;
	HP = 70;
	state = STATE_IDLE;
	attackRange = 200;
	attackCoolTime = 200;
	col = new Collider(Vector2D<float>(animation[direction].size.right, animation[direction].size.bottom));
	col->owner = this;
	col->layer = enemy;
	col->pos = pos;
	col->damage = 5;
	frame = 0;
	COLL.emplace_back(col);
}



Bombshe::~Bombshe()
{
	shadow.Destroy();
	DestroyImage();
}

void Bombshe::draw_character(HDC mDC)
{
	float yDest = pos.y - (animation[direction].size.bottom - 22) * 2;
	shadow.Draw(mDC, pos.x - shadow.GetWidth(), pos.y + animation[direction].size.bottom - 2 - shadow.GetHeight(), shadow.GetWidth() * 2, shadow.GetHeight() * 2);
	animation[direction].resource.Draw(mDC, pos.x - animation[direction].size.right, yDest - 20, animation[direction].size.right * 2, animation[direction].size.bottom * 2,
		(int)frame * animation[direction].size.right, 0, animation[direction].size.right, animation[direction].size.bottom);
	if (isAttack&&lookRange) {
		HPEN old = (HPEN)SelectObject(mDC, GREENP);
		Arc(mDC, pos.x-attackSize, pos.y - attackSize, pos.x + attackSize, pos.y + attackSize, 0,0,0,0);
		SelectObject(mDC, old);
	}
}

void Bombshe::handle_event()
{
	if (attackable() && !targetLocked || (state == STATE_DAMAGED && frame == 1)) {
		targetLocked = true;
		state = STATE_RUN;
		DestroyImage();
		SetImage(state);
		frame = 0;
	}
	if(targetLocked) {
		if (!isAttack&&(int)frame==4) {
			wave = new Effect(L"banshe_effect.png", col->pos, 1, 13);
			EffectManager::getInstance()->set_effect(wave);
			isAttack = true;
		}
		if (isAttack) {
			attack();
			if ((int)(wave->time+1) == wave->effect.frame) {
				if (wave->effect.frame == 13) {
					wave->effect.resource.Destroy();
					wave->effect.resource.Load(L"banshe_effect2.png");
					wave->effect.frame = 3;
					wave->effect.size = { 0,0,wave->effect.resource.GetWidth() / wave->effect.frame ,wave->effect.resource.GetHeight() };
					wave->time = 0;
					wave->velocity = 2.5;
				}
				else if(wave->effect.frame == 3)
					wave->time = 0;
			}
			if (state == STATE_DAMAGED) {
				state = STATE_RUN;
				DestroyImage();
				SetImage(state);
				frame = 0;
			}
		}
	}
}

void Bombshe::update()
{
	if(state == STATE_IDLE){
		frame = (frame + frame_time * 2 * animation[direction].frame);
		if (frame >= animation[direction].frame) frame = 0;
		SetDirection();
		col->pos = pos;
	}
	else if (state == STATE_RUN&&(int)frame<5) {
		frame = (frame + frame_time * 2 * animation[direction].frame);
		if (frame >= animation[direction].frame) frame = 0;
		if (attackSize < 100)
			attackSize += 1;
		SetDirection();
		col->pos = pos;
	}
	else if (state == STATE_DEAD) {
		if ((int)frame < animation[direction].frame)
			frame = (frame + frame_time * 3 * animation[direction].frame);
		else {
			EnemyManager::getInstance()->delete_enemy(this);
			deleteSet.insert(this);
			EffectManager::getInstance()->set_effect(new Effect(L"Bombshe_explode.png", pos, 3, 5));
		}
	}
	else if (state == STATE_DAMAGED) {
		frame = (frame + frame_time * 2 * animation[direction].frame);
	}
}

void Bombshe::SetImage(int state)
{
	switch (state)
	{
	case STATE_IDLE:
		animation[FRONT].resource.Load(L"Bombshe_front.png");
		animation[FRONT_RIGHT].resource.Load(L"Bombshe_right.png");
		animation[FRONT_LEFT].resource.Load(L"Bombshe_left.png");
		animation[BACK].resource.Load(L"Bombshe_front.png");
		animation[BACK_RIGHT].resource.Load(L"Bombshe_right.png");
		animation[BACK_LEFT].resource.Load(L"Bombshe_left.png");
		for (int i = 0; i < 6; i++) {
			animation[i].frame = 4;
			animation[i].size = { 0,0,animation[i].resource.GetWidth() / animation[i].frame,animation[i].resource.GetHeight() };
		}
		break;
	case STATE_RUN:
		animation[FRONT].resource.Load(L"Bombshe_attack.png");
		animation[FRONT_RIGHT].resource.Load(L"Bombshe_attack.png");
		animation[FRONT_LEFT].resource.Load(L"Bombshe_attack.png");
		animation[BACK].resource.Load(L"Bombshe_attack.png");
		animation[BACK_RIGHT].resource.Load(L"Bombshe_attack.png");
		animation[BACK_LEFT].resource.Load(L"Bombshe_attack.png");
		for (int i = 0; i < 6; i++) {
			animation[i].frame = 5;
			animation[i].size = { 0,0,animation[i].resource.GetWidth() / animation[i].frame,animation[i].resource.GetHeight() };
		}
		break;
	case STATE_DAMAGED:
		animation[FRONT].resource.Load(L"Bombshe_damaged.png");
		animation[FRONT_RIGHT].resource.Load(L"Bombshe_damaged.png");
		animation[FRONT_LEFT].resource.Load(L"Bombshe_damaged.png");
		animation[BACK].resource.Load(L"Bombshe_damaged.png");
		animation[BACK_RIGHT].resource.Load(L"Bombshe_damaged.png");
		animation[BACK_LEFT].resource.Load(L"Bombshe_damaged.png");
		for (int i = 0; i < 6; i++) {
			animation[i].frame = 1;
			animation[i].size = { 0,0,animation[i].resource.GetWidth() / animation[i].frame,animation[i].resource.GetHeight() };
		}
		break;
	case STATE_DEAD:
		animation[FRONT].resource.Load(L"Bombshe_dead.png");
		animation[FRONT_RIGHT].resource.Load(L"Bombshe_dead.png");
		animation[FRONT_LEFT].resource.Load(L"Bombshe_dead.png");
		animation[BACK].resource.Load(L"Bombshe_dead.png");
		animation[BACK_RIGHT].resource.Load(L"Bombshe_dead.png");
		animation[BACK_LEFT].resource.Load(L"Bombshe_dead.png");
		for (int i = 0; i < 6; i++) {
			animation[i].frame = 2;
			animation[i].size = { 0,0,animation[i].resource.GetWidth() / animation[i].frame,animation[i].resource.GetHeight() };
		}
		break;
	default:
		break;
	}
}

void Bombshe::SetDirection()
{
	angle = std::atan2(target->GetPos().y - pos.y, target->GetPos().x - pos.x) * (180.0f / M_PI);
	if (angle >= -20 && angle <= 60) {
		direction = FRONT_RIGHT;
	}
	else if (angle > 60 && angle <= 120) {
		direction = FRONT;
	}
	else if (angle >= 120 && angle <= 180 || angle > -180 && angle < -160) {
		direction = FRONT_LEFT;
	}
	else if (angle >= -160 && angle <= -120) {
		direction = BACK_LEFT;
	}
	else if (angle >= -120 && angle <= -60) {
		direction = BACK;
	}
	else if (angle >= -60 && angle < -20) {
		direction = BACK_RIGHT;
	}
}

void Bombshe::attack()
{
	for (auto& other : COLL) {
		for (int i = 0; i < 4; i++) {
			if (other->layer == player) {
				Vector2D<float> dot[4] = { Vector2D<float>(other->pos.x - other->size.x, other->pos.y - other->size.y),
				Vector2D<float>(other->pos.x + other->size.x, other->pos.y - other->size.y),
				Vector2D<float>(other->pos.x + other->size.x, other->pos.y + other->size.y),
				Vector2D<float>(other->pos.x - other->size.x, other->pos.y + other->size.y) };
				if ((dot[i] - pos).GetLenth() <= attackSize) {
					other->owner->handle_collision(enemyBullet, 1);
					break;
				}
			}
		}
	}
}

void Bombshe::DestroyImage()
{
	for (int i = 0; i < 6; i++)
		animation[i].resource.Destroy();
}

void Bombshe::handle_collision(int otherLayer, int damage)
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

	case rolled_player:
	case playerMelee:
		EffectManager::getInstance()->set_effect(new Effect(L"melee_effect.png", col->pos, 4, 3));
		HP -= damage;
		if (HP <= 0) {
			state = STATE_DEAD;
			for (auto i = COLL.begin(); i != COLL.end(); ++i)
				if (COLL[i - COLL.begin()] == this->col)
				{
					COLL.erase(i);
					break;
				}
			delete this->col;
			this->col = nullptr;
			wave->time = wave->effect.frame;
		}
		else state = STATE_DAMAGED;
		DestroyImage();
		SetImage(state);
		frame = 0;
		break;
	case playerBullet:
		HP -= damage;
		if (HP <= 0) {
			state = STATE_DEAD;
			for (auto i = COLL.begin(); i != COLL.end(); ++i)
				if (COLL[i - COLL.begin()] == this->col)
				{
					COLL.erase(i);
					break;
				}
			delete this->col;
			this->col = nullptr;
			wave->time = wave->effect.frame;
		}
		else state = STATE_DAMAGED;
		DestroyImage();
		SetImage(state);
		frame = 0;
		break;
	default:
		break;
	}
}

