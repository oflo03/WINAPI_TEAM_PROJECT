#include "PistolMan.h"
#include"EnemyDamaged.h"
#include"EnemyIdle.h"

extern double frame_time;

PistolMan::PistolMan(double x, double y, Player* target) : Enemy(x, y, target)
{
	SetImage(STATE_IDLE);
	hand.Load(L"hand.png");
	velocity = 100;
	state = new EnemyIdle();
	weapon = new Pistol();
	attackRange = 800;
	attackCoolTime = 0;
	col = new Collider(Vector2D<float>(animation[direction].size.right, animation[direction].size.bottom));
	col->owner = this;
	col->layer = enemy;
	col->pos = pos;
	COLL.emplace_back(col);
}



PistolMan::~PistolMan()
{
	delete weapon;
	DestroyImage();
}

void PistolMan::draw_character(HDC mDC)
{
	handPos = pos;
	if (abs(angle) < 90)
	{
		handPos.x += 18;
		handPos.y += 8;
	}
	else
	{
		handPos.x -= 17;
		handPos.y += 8;
	}
	float yDest = pos.y - (animation[direction].size.bottom - 20) * 2;
	if (direction == FRONT || direction == FRONT_RIGHT || direction == FRONT_LEFT) {
		animation[direction].resource.Draw(mDC, pos.x - animation[direction].size.right, yDest - 20, animation[direction].size.right * 2, animation[direction].size.bottom * 2,
			(int)frame * animation[direction].size.right, 0, animation[direction].size.right, animation[direction].size.bottom
		);
		weapon->draw_weapon(mDC, handPos, target->GetPos());
		hand.Draw(mDC, handPos.x - hand.GetWidth(), handPos.y - hand.GetHeight(), hand.GetWidth() * 2, hand.GetHeight() * 2);
	}
	else {
		weapon->draw_weapon(mDC, handPos, target->GetPos());
		hand.Draw(mDC, handPos.x - hand.GetWidth(), handPos.y - hand.GetHeight(), hand.GetWidth() * 2, hand.GetHeight() * 2);
		animation[direction].resource.Draw(mDC, pos.x - animation[direction].size.right, yDest - 20, animation[direction].size.right * 2, animation[direction].size.bottom * 2,
			(int)frame * animation[direction].size.right, 0, animation[direction].size.right, animation[direction].size.bottom
		);
	}
}

void PistolMan::handle_event()
{
	EnemyState* temp = state->handle_event(*this);
	if (temp != nullptr) {
		state->exit(*this);
		delete state;
		state = temp;
		state->enter(*this);
		frame = 0;
	}
	if (weapon->IsRunOut() && attackCoolTime == 0)
		attackCoolTime = 100;
	else if (weapon->IsRunOut() && attackCoolTime == 1)
		weapon->ReLoad();
}

void PistolMan::update()
{
	state->update(*this);
	if (dynamic_cast<EnemyDamaged*>(state) == nullptr)
		frame = (frame + frame_time * 2 * animation[direction].frame);
	else
		frame = (frame + frame_time * 10 * animation[direction].frame);
	if (frame >= animation[direction].frame) frame = 0;
	weapon->update();
	if (attackCoolTime)
		attackCoolTime--;
	col->pos = pos;
}

void PistolMan::SetImage(int state)
{
	switch (state)
	{
	case STATE_IDLE:
		animation[FRONT].resource.Load(L"enemy_pistol_right.png");
		animation[FRONT_RIGHT].resource.Load(L"enemy_pistol_right.png");
		animation[FRONT_LEFT].resource.Load(L"enemy_pistol_left.png");
		animation[BACK].resource.Load(L"enemy_pistol_back.png");
		animation[BACK_RIGHT].resource.Load(L"enemy_pistol_back.png");
		animation[BACK_LEFT].resource.Load(L"enemy_pistol_back.png");
		for (int i = 0; i < 6; i++) {
			animation[i].frame = 2;
			animation[i].size = { 0,0,animation[i].resource.GetWidth() / animation[i].frame,animation[i].resource.GetHeight() };
		}
		break;
	case STATE_RUN:
		animation[FRONT].resource.Load(L"enemy_pistol_run_front.png");
		animation[FRONT_RIGHT].resource.Load(L"enemy_pistol_run_right.png");
		animation[FRONT_LEFT].resource.Load(L"enemy_pistol_run_left.png");
		animation[BACK].resource.Load(L"enemy_pistol_run_back.png");
		animation[BACK_RIGHT].resource.Load(L"enemy_pistol_run_back.png");
		animation[BACK_LEFT].resource.Load(L"enemy_pistol_run_back.png");
		for (int i = 0; i < 6; i++) {
			animation[i].frame = 6;
			animation[i].size = { 0,0,animation[i].resource.GetWidth() / animation[i].frame,animation[i].resource.GetHeight() };
		}
		break;
	case STATE_DAMAGED:
		animation[FRONT].resource.Load(L"enemy_pistol_damaged_front.png");
		animation[FRONT_RIGHT].resource.Load(L"enemy_pistol_damaged_right.png");
		animation[FRONT_LEFT].resource.Load(L"enemy_pistol_damaged_left.png");
		animation[BACK].resource.Load(L"enemy_pistol_damaged_front.png");
		animation[BACK_RIGHT].resource.Load(L"enemy_pistol_damaged_right.png");
		animation[BACK_LEFT].resource.Load(L"enemy_pistol_damaged_left.png");
		for (int i = 0; i < 6; i++) {
			animation[i].frame = 2;
			animation[i].size = { 0,0,animation[i].resource.GetWidth() / animation[i].frame,animation[i].resource.GetHeight() };
		}
		break;
	default:
		break;
	}
}

void PistolMan::SetDirection()
{
	if (target != nullptr) angle = std::atan2(dir.y, dir.x) * (180.0f / M_PI);
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

void PistolMan::attack()
{
	weapon->attack(handPos, target->GetPos(), enemyBullet);
}

void PistolMan::DestroyImage()
{
	for (int i = 0; i < 6; i++)
		animation[i].resource.Destroy();
}

void PistolMan::handle_collision(int otherLayer, int damage)
{
	switch (otherLayer)
	{
	case wall:
		if (!isWallCollision(Vector2D<float>(pos.x, lastPos.y), col->size))
			pos.y = lastPos.y;
		else if (!isWallCollision(Vector2D<float>(lastPos.x, pos.y), col->size))
			pos.x = lastPos.x;
		else
			pos = lastPos;
		lastPos = pos;
		col->pos = pos;
		break;
	case rolled_player:
		state->exit(*this);
		delete state;
		state = new EnemyDamaged();
		state->enter(*this);
		frame = 0;
		lastPos = pos;
		pos -= dir * 10;
		break;
	case playerMelee:
		state->exit(*this);
		delete state;
		state = new EnemyDamaged();
		state->enter(*this);
		frame = 0;
		lastPos = pos;
		pos -= dir * 10;
		break;
	case playerBullet:
		state->exit(*this);
		delete state;
		state = new EnemyDamaged();
		state->enter(*this);
		frame = 0;
		lastPos = pos;
		pos -= dir * 2;
		break;
	default:
		break;
	}
}
