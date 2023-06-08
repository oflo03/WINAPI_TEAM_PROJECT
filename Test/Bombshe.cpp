#include "Bombshe.h"
#include"EffectManager.h"

extern double frame_time;
extern std::uniform_int_distribution<int> rad;
extern std::uniform_int_distribution<int> ranTime;
extern std::uniform_int_distribution<int> ran;

Bombshe::Bombshe(double x, double y, Player* target) : Enemy(x, y)
{
	SetImage(STATE_IDLE);
	shadow.Load(L"shadow.png");
	attackSize = 0;
	velocity = 100;
	moveTime = 200;
	state = STATE_IDLE;
	attackRange = 200;
	attackCoolTime = 200;
	col = new Collider(Vector2D<float>(animation[direction].size.right, animation[direction].size.bottom));
	col->owner = this;
	col->layer = enemy;
	col->pos = pos;
	col->damage = 5;
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
	shadow.Draw(mDC, pos.x - shadow.GetWidth(), pos.y + col->size.y - 2 - shadow.GetHeight(), shadow.GetWidth() * 2, shadow.GetHeight() * 2);
	animation[direction].resource.Draw(mDC, pos.x - animation[direction].size.right, yDest - 20, animation[direction].size.right * 2, animation[direction].size.bottom * 2,
		(int)frame * animation[direction].size.right, 0, animation[direction].size.right, animation[direction].size.bottom);
}

void Bombshe::handle_event()
{
	if (attackable()){
		targetLocked = true;
		state = STATE_RUN;
		DestroyImage();
		SetImage(state);
		frame = 0;
	}
	if(targetLocked) {
		if(frame > 4.5&&frame<5)EffectManager::getInstance()->set_effect(new Effect(L"banshe_effect.png", col->pos, 4, 13));
		if((int)frame >= 4)
			attack();
	}
}

void Bombshe::update()
{
	if(state == STATE_IDLE){
		frame = (frame + frame_time * 2 * animation[direction].frame);
		if (frame >= animation[direction].frame) frame = 0;
	}
	else if (state == STATE_RUN&&(int)frame<5) {
		frame = (frame + frame_time * 2 * animation[direction].frame);
		if (attackSize < 160)
			attackSize += 5;
	}
	SetDirection();
	col->pos = pos;
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
			animation[i].frame = 4;
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
		moveTime = 1;
		frame = 0;
		break;
	case playerBullet:
		moveTime = 1;
		frame = 0;
		break;
	default:
		break;
	}
}

