#include "ShotgunMan.h"

extern double frame_time;
extern std::uniform_int_distribution<int> rad;
extern std::uniform_int_distribution<int> ranTime;
extern std::uniform_int_distribution<int> ran;

ShotgunMan::ShotgunMan(double x, double y, Player* target) : Enemy(x, y, target)
{
	SetImage(STATE_IDLE);
	hand.Load(L"enemy_pistol_hand.png");
	velocity = 100;
	moveTime = 200;
	state = STATE_IDLE;
	weapon = new Shotgun();
	weapon->Enemy();
	attackRange = 500;
	attackCoolTime = 0;
	col = new Collider(Vector2D<float>(animation[direction].size.right, animation[direction].size.bottom));
	col->owner = this;
	col->layer = enemy;
	col->pos = pos;
	col->damage = 5;
	COLL.emplace_back(col);
}



ShotgunMan::~ShotgunMan()
{
	delete weapon;
	DestroyImage();
}

void ShotgunMan::draw_character(HDC mDC)
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

void ShotgunMan::handle_event()
{
	if (!attackable()) {
		state = STATE_IDLE;
		DestroyImage();
		SetImage(state);
		dir.x = dir.y = 0;
	}
	else {
		attack();
		if ((int)moveTime == 0) {
			if (state == STATE_DAMAGED) {
				state = STATE_IDLE;
				dir.x = dir.y = 0;
				moveTime = 50;
			}
			else {
				moveTime = ranTime(dre);
				state = ran(dre);
				if (state == STATE_IDLE)
					dir.x = dir.y = 0;
				else if (state == STATE_RUN)
					dir = Vector2D<float>(1, 0).Rotate(rad(dre));
			}
			DestroyImage();
			SetImage(state);
			frame = 0;
		}
	}
	if (weapon->IsRunOut() && attackCoolTime == 0)
		attackCoolTime = 300;
	else if (weapon->IsRunOut() && attackCoolTime == 1)
		weapon->ReLoad();
}

void ShotgunMan::update()
{
	lastPos = pos;
	if (state != STATE_DAMAGED) {
		pos = pos + dir * velocity * frame_time;
		frame = (frame + frame_time * 2 * animation[direction].frame);
		if ((int)moveTime)moveTime--;
	}
	else {
		frame = (frame + frame_time * 10 * animation[direction].frame);
		if ((int)moveTime) moveTime -= frame_time * 10 * 2;
	}
	if (frame >= animation[direction].frame) frame = 0;
	SetDirection();
	weapon->update();
	if (attackCoolTime)
		attackCoolTime--;
	col->pos = pos;
}

void ShotgunMan::SetImage(int state)
{
	switch (state)
	{
	case STATE_IDLE:
		animation[FRONT].resource.Load(L"enemy_shotgun_front.png");
		animation[FRONT_RIGHT].resource.Load(L"enemy_shotgun_front.png");
		animation[FRONT_LEFT].resource.Load(L"enemy_shotgun_front.png");
		animation[BACK].resource.Load(L"enemy_shotgun_back.png");
		animation[BACK_RIGHT].resource.Load(L"enemy_shotgun_back.png");
		animation[BACK_LEFT].resource.Load(L"enemy_shotgun_back.png");
		for (int i = 0; i < 6; i++) {
			animation[i].frame = 2;
			animation[i].size = { 0,0,animation[i].resource.GetWidth() / animation[i].frame,animation[i].resource.GetHeight() };
		}
		break;
	case STATE_RUN:
		animation[FRONT].resource.Load(L"enemy_shotgun_run_front.png");
		animation[FRONT_RIGHT].resource.Load(L"enemy_shotgun_run_right.png");
		animation[FRONT_LEFT].resource.Load(L"enemy_shotgun_run_left.png");
		animation[BACK].resource.Load(L"enemy_shotgun_run_back.png");
		animation[BACK_RIGHT].resource.Load(L"enemy_shotgun_run_back.png");
		animation[BACK_LEFT].resource.Load(L"enemy_shotgun_run_back.png");
		for (int i = 0; i < 6; i++) {
			animation[i].frame = 6;
			animation[i].size = { 0,0,animation[i].resource.GetWidth() / animation[i].frame,animation[i].resource.GetHeight() };
		}
		break;
	case STATE_DAMAGED:
		animation[FRONT].resource.Load(L"enemy_shotgun_damaged_front.png");
		animation[FRONT_RIGHT].resource.Load(L"enemy_shotgun_damaged_right.png");
		animation[FRONT_LEFT].resource.Load(L"enemy_shotgun_damaged_left.png");
		animation[BACK].resource.Load(L"enemy_shotgun_damaged_front.png");
		animation[BACK_RIGHT].resource.Load(L"enemy_shotgun_damaged_right.png");
		animation[BACK_LEFT].resource.Load(L"enemy_shotgun_damaged_left.png");
		for (int i = 0; i < 6; i++) {
			animation[i].frame = 2;
			animation[i].size = { 0,0,animation[i].resource.GetWidth() / animation[i].frame,animation[i].resource.GetHeight() };
		}
		break;
	default:
		break;
	}
}

void ShotgunMan::SetDirection()
{
	if (target != nullptr) angle = std::atan2(target->GetPos().y - pos.y, target->GetPos().x - pos.x) * (180.0f / M_PI);
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

void ShotgunMan::attack()
{
	weapon->attack(handPos, target->GetPos(), enemyBullet);
}

void ShotgunMan::DestroyImage()
{
	for (int i = 0; i < 6; i++)
		animation[i].resource.Destroy();
}

void ShotgunMan::handle_collision(int otherLayer, int damage)
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
		state = STATE_DAMAGED;
		DestroyImage();
		SetImage(state);
		moveTime = 2;
		frame = 0;
		lastPos = pos;
		pos -= (target->GetPos() - pos).Normalize() * 10;
		if (!isWallCollision(Vector2D<float>(pos.x, lastPos.y), col->size))
			pos.y = lastPos.y;
		else if (!isWallCollision(Vector2D<float>(lastPos.x, pos.y), col->size))
			pos.x = lastPos.x;
		else
			pos = lastPos;
		lastPos = pos;
		col->pos = pos;
		break;
	case playerMelee:
		state = STATE_DAMAGED;
		DestroyImage();
		SetImage(state);
		moveTime = 2;
		frame = 0;
		lastPos = pos;
		pos -= (target->GetPos() - pos).Normalize() * 10;
		if (!isWallCollision(Vector2D<float>(pos.x, lastPos.y), col->size))
			pos.y = lastPos.y;
		else if (!isWallCollision(Vector2D<float>(lastPos.x, pos.y), col->size))
			pos.x = lastPos.x;
		else
			pos = lastPos;
		lastPos = pos;
		col->pos = pos;
		break;
	case playerBullet:
		state = STATE_DAMAGED;
		DestroyImage();
		SetImage(state);
		moveTime = 2;
		frame = 0;
		lastPos = pos;
		pos -= (target->GetPos() - pos).Normalize() * 2;
		if (!isWallCollision(Vector2D<float>(pos.x, lastPos.y), col->size))
			pos.y = lastPos.y;
		else if (!isWallCollision(Vector2D<float>(lastPos.x, pos.y), col->size))
			pos.x = lastPos.x;
		else
			pos = lastPos;
		lastPos = pos;
		col->pos = pos;
		break;
	default:
		break;
	}
}


