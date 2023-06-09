#include "ShotgunMan.h"
#include"EffectManager.h"
#include"EnemyManager.h"
#include"DropItem.h"

extern double frame_time;
extern std::uniform_int_distribution<int> rad;
extern std::uniform_int_distribution<int> ranTime;
extern std::uniform_int_distribution<int> ran;
extern std::uniform_int_distribution<int> randrop;
extern std::vector<DropItem*> drops;

Animation ShotgunMan::animation[4][6];

void ShotgunMan::init()
{
	animation[STATE_IDLE][FRONT].resource.Load(L"enemy_shotgun_front.png");
	animation[STATE_IDLE][FRONT_RIGHT].resource.Load(L"enemy_shotgun_front.png");
	animation[STATE_IDLE][FRONT_LEFT].resource.Load(L"enemy_shotgun_front.png");
	animation[STATE_IDLE][BACK].resource.Load(L"enemy_shotgun_back.png");
	animation[STATE_IDLE][BACK_RIGHT].resource.Load(L"enemy_shotgun_back.png");
	animation[STATE_IDLE][BACK_LEFT].resource.Load(L"enemy_shotgun_back.png");
	for (int i = 0; i < 6; i++) {
		animation[STATE_IDLE][i].frame = 2;
		animation[STATE_IDLE][i].size = { 0,0,animation[STATE_IDLE][i].resource.GetWidth() / animation[STATE_IDLE][i].frame,animation[STATE_IDLE][i].resource.GetHeight() };
		animation[STATE_IDLE][i].velocity = 2;
	}
	animation[STATE_RUN][FRONT].resource.Load(L"enemy_shotgun_run_front.png");
	animation[STATE_RUN][FRONT_RIGHT].resource.Load(L"enemy_shotgun_run_right.png");
	animation[STATE_RUN][FRONT_LEFT].resource.Load(L"enemy_shotgun_run_left.png");
	animation[STATE_RUN][BACK].resource.Load(L"enemy_shotgun_run_back.png");
	animation[STATE_RUN][BACK_RIGHT].resource.Load(L"enemy_shotgun_run_back.png");
	animation[STATE_RUN][BACK_LEFT].resource.Load(L"enemy_shotgun_run_back.png");
	for (int i = 0; i < 6; i++) {
		animation[STATE_RUN][i].frame = 6;
		animation[STATE_RUN][i].size = { 0,0,animation[STATE_RUN][i].resource.GetWidth() / animation[STATE_RUN][i].frame,animation[STATE_RUN][i].resource.GetHeight() };
		animation[STATE_RUN][i].velocity = 2;
	}
	animation[STATE_DAMAGED][FRONT].resource.Load(L"enemy_shotgun_damaged_front.png");
	animation[STATE_DAMAGED][FRONT_RIGHT].resource.Load(L"enemy_shotgun_damaged_right.png");
	animation[STATE_DAMAGED][FRONT_LEFT].resource.Load(L"enemy_shotgun_damaged_left.png");
	animation[STATE_DAMAGED][BACK].resource.Load(L"enemy_shotgun_damaged_front.png");
	animation[STATE_DAMAGED][BACK_RIGHT].resource.Load(L"enemy_shotgun_damaged_right.png");
	animation[STATE_DAMAGED][BACK_LEFT].resource.Load(L"enemy_shotgun_damaged_left.png");
	for (int i = 0; i < 6; i++) {
		animation[STATE_DAMAGED][i].frame = 2;
		animation[STATE_DAMAGED][i].size = { 0,0,animation[STATE_DAMAGED][i].resource.GetWidth() / animation[STATE_DAMAGED][i].frame,animation[STATE_DAMAGED][i].resource.GetHeight() };
		animation[STATE_DAMAGED][i].velocity = 2;
	}
	animation[STATE_DEAD][FRONT].resource.Load(L"enemy_shotgun_dead.png");
	animation[STATE_DEAD][FRONT_RIGHT].resource.Load(L"enemy_shotgun_dead.png");
	animation[STATE_DEAD][FRONT_LEFT].resource.Load(L"enemy_shotgun_dead.png");
	animation[STATE_DEAD][BACK].resource.Load(L"enemy_shotgun_dead.png");
	animation[STATE_DEAD][BACK_RIGHT].resource.Load(L"enemy_shotgun_dead.png");
	animation[STATE_DEAD][BACK_LEFT].resource.Load(L"enemy_shotgun_dead.png");
	for (int i = 0; i < 6; i++) {
		animation[STATE_DEAD][i].frame = 3;
		animation[STATE_DEAD][i].size = { 0,0,animation[STATE_DEAD][i].resource.GetWidth() / animation[STATE_DEAD][i].frame,animation[STATE_DEAD][i].resource.GetHeight() };
		animation[STATE_DEAD][i].velocity = 2;
	}
}

void ShotgunMan::release()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++)
			animation[i][j].resource.Destroy();
	}
}

ShotgunMan::ShotgunMan(double x, double y, Player* target) : Enemy(x, y)
{
	hand.Load(L"enemy_pistol_hand.png");
	shadow.Load(L"shadow.png");
	velocity = 100;
	moveTime = 200;
	HP = 50;
	state = STATE_IDLE;
	weapon = new Shotgun();
	weapon->Enemy();
	attackRange = 300;
	attackCoolTime = 0;
	col = new Collider(Vector2D<float>(animation[STATE_IDLE][FRONT].size.right, animation[STATE_IDLE][FRONT].size.bottom));
	col->owner = this;
	col->layer = enemy;
	col->pos = pos;
	col->damage = 5;
	COLL.emplace_back(col);
}

ShotgunMan::~ShotgunMan()
{
	delete weapon;
	hand.Destroy();
	shadow.Destroy();
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
	float yDest = pos.y - (animation[STATE_IDLE][FRONT].size.bottom - 25) * 2;
	if (state != STATE_DEAD) {
		shadow.Draw(mDC, pos.x - shadow.GetWidth(), pos.y + col->size.y - 2 - shadow.GetHeight(), shadow.GetWidth() * 2, shadow.GetHeight() * 2);
		if (direction == FRONT || direction == FRONT_RIGHT || direction == FRONT_LEFT) {
			animation[state][direction].resource.Draw(mDC, pos.x - animation[state][direction].size.right, yDest - 20, animation[state][direction].size.right * 2, animation[state][direction].size.bottom * 2,
				(int)frame * animation[state][direction].size.right, 0, animation[state][direction].size.right, animation[state][direction].size.bottom
			);
			weapon->draw_weapon(mDC, handPos, target->GetPos());
			hand.Draw(mDC, handPos.x - hand.GetWidth(), handPos.y - hand.GetHeight(), hand.GetWidth() * 2, hand.GetHeight() * 2);
		}
		else {
			weapon->draw_weapon(mDC, handPos, target->GetPos());
			hand.Draw(mDC, handPos.x - hand.GetWidth(), handPos.y - hand.GetHeight(), hand.GetWidth() * 2, hand.GetHeight() * 2);
			animation[state][direction].resource.Draw(mDC, pos.x - animation[state][direction].size.right, yDest - 20, animation[state][direction].size.right * 2, animation[state][direction].size.bottom * 2,
				(int)frame * animation[state][direction].size.right, 0, animation[state][direction].size.right, animation[state][direction].size.bottom
			);
		}
	}
	else
		animation[state][direction].resource.Draw(mDC, pos.x - animation[state][direction].size.right, yDest - 20, animation[state][direction].size.right * 2, animation[state][direction].size.bottom * 2,
			(int)frame * animation[state][direction].size.right, 0, animation[state][direction].size.right, animation[state][direction].size.bottom);
}

void ShotgunMan::handle_event()
{
	if (!attackable()) {
		state = STATE_RUN;
		dir = (target->GetPos() - pos).Normalize();
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
	if (state == STATE_DEAD) {
		if ((int)frame < animation[state][direction].frame)
			frame = (frame + frame_time * animation[state][direction].velocity * animation[state][direction].frame);
		else {
			EnemyManager::getInstance()->delete_enemy(this);
			deleteSet.insert(this);
			int num = randrop(dre);
			if (num == 0) {
				drops.emplace_back(new DropItem(DROP::DSHOTGUN, pos));
			}
			EffectManager::getInstance()->set_effect(new Effect(CEffect::SHOTGUNDIE, pos));
		}
	}
	else {
		frame = (frame + frame_time * animation[state][direction].velocity * animation[state][direction].frame);
		if (state == STATE_DAMAGED) {
			if (moveTime >= 0) moveTime -= frame_time * 2;
		}
		else {
			pos = pos + dir * velocity * frame_time;
			if ((int)moveTime)moveTime--;
			if ((int)(frame) == animation[state][direction].frame) frame = 0;
		}
		SetDirection();
		weapon->update();
		if (attackCoolTime)
			attackCoolTime--;
		col->pos = pos;
	}
}

void ShotgunMan::SetDirection()
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

void ShotgunMan::attack()
{
	weapon->attack(handPos, target->GetPos(), enemyBullet);
}


void ShotgunMan::handle_collision(int otherLayer, int damage)
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
		EffectManager::getInstance()->set_effect(new Effect(CEffect::SWORDATTACK, col->pos));
		moveTime = 2;
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
		}
		else state = STATE_DAMAGED;
		frame = 0;
		break;
	case playerBullet:
		moveTime = 2;
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
		}
		else state = STATE_DAMAGED;
		frame = 0;
		break;
	default:
		break;
	}
}


