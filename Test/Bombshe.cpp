#include "Bombshe.h"
#include"EnemyManager.h"
#include"DropItem.h"

extern double frame_time;
extern std::uniform_int_distribution<int> rad;
extern std::uniform_int_distribution<int> ranTime;
extern std::uniform_int_distribution<int> ran;
extern std::uniform_int_distribution<int> randrop;
extern std::vector<DropItem*> drops;
extern bool lookRange;
extern HPEN GREENP;

enum BOMBSTATE {
	BIDLE, BATTACK, BDAMAGED, BDEAD
};

Animation Bombshe::animation[4][3];

Bombshe::Bombshe(double x, double y, Player* target) : Enemy(x, y), isAttack(false)
{
	shadow.Load(L"resources/shadow.png");
	attackSize = 0;
	velocity = 100;
	moveTime = 200;
	HP = 70;
	state = STATE_IDLE;
	attackRange = 200;
	attackCoolTime = 200;
	wave = nullptr;
	lastPos = pos;
}



Bombshe::~Bombshe()
{
	shadow.Destroy();
}

void Bombshe::init()
{
	animation[BIDLE][FRONT].resource.Load(L"resources/Bombshe_front.png");
	animation[BIDLE][FRONT_RIGHT].resource.Load(L"resources/Bombshe_right.png");
	animation[BIDLE][FRONT_LEFT].resource.Load(L"resources/Bombshe_left.png");
	for (int i = 0; i < 3; i++) {
		animation[BIDLE][i].frame = 4;
		animation[BIDLE][i].size = { 0,0,animation[BIDLE][i].resource.GetWidth() / animation[BIDLE][i].frame,animation[BIDLE][i].resource.GetHeight() };
		animation[BIDLE][i].velocity = 2;
	}
	animation[BATTACK][FRONT].resource.Load(L"resources/Bombshe_attack.png");
	animation[BATTACK][FRONT_RIGHT].resource.Load(L"resources/Bombshe_attack.png");
	animation[BATTACK][FRONT_LEFT].resource.Load(L"resources/Bombshe_attack.png");
	for (int i = 0; i < 3; i++) {
		animation[BATTACK][i].frame = 5;
		animation[BATTACK][i].size = { 0,0,animation[BATTACK][i].resource.GetWidth() / animation[BATTACK][i].frame,animation[BATTACK][i].resource.GetHeight() };
		animation[BATTACK][i].velocity = 2;
	}
	animation[BDAMAGED][FRONT].resource.Load(L"resources/Bombshe_damaged.png");
	animation[BDAMAGED][FRONT_RIGHT].resource.Load(L"resources/Bombshe_damaged.png");
	animation[BDAMAGED][FRONT_LEFT].resource.Load(L"resources/Bombshe_damaged.png");
	for (int i = 0; i < 3; i++) {
		animation[BDAMAGED][i].frame = 1;
		animation[BDAMAGED][i].size = { 0,0,animation[BDAMAGED][i].resource.GetWidth() / animation[BDAMAGED][i].frame,animation[BDAMAGED][i].resource.GetHeight() };
		animation[BDAMAGED][i].velocity = 8;
	}
	animation[BDEAD][FRONT].resource.Load(L"resources/Bombshe_dead.png");
	animation[BDEAD][FRONT_RIGHT].resource.Load(L"resources/Bombshe_dead.png");
	animation[BDEAD][FRONT_LEFT].resource.Load(L"resources/Bombshe_dead.png");
	for (int i = 0; i < 3; i++) {
		animation[BDEAD][i].frame = 2;
		animation[BDEAD][i].size = { 0,0,animation[BDEAD][i].resource.GetWidth() / animation[BDEAD][i].frame,animation[BDEAD][i].resource.GetHeight() };
		animation[BDEAD][i].velocity = 3;
	}
}

void Bombshe::release()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++)
			animation[i][j].resource.Destroy();
	}
}

void Bombshe::draw_character(HDC mDC)
{
	if (col || HP <= 0) {
		float yDest = pos.y - (animation[BIDLE][FRONT].size.bottom - 22) * 2;
		shadow.Draw(mDC, pos.x - shadow.GetWidth(), pos.y + animation[state][direction].size.bottom - 2 - shadow.GetHeight(), shadow.GetWidth() * 2, shadow.GetHeight() * 2);
		animation[state][direction].resource.Draw(mDC, pos.x - animation[state][direction].size.right, yDest - 20, animation[state][direction].size.right * 2, animation[state][direction].size.bottom * 2,
			(int)frame * animation[state][direction].size.right, 0, animation[state][direction].size.right, animation[state][direction].size.bottom);
		if (isAttack && lookRange) {
			HPEN old = (HPEN)SelectObject(mDC, GREENP);
			Arc(mDC, pos.x - attackSize, pos.y - attackSize, pos.x + attackSize, pos.y + attackSize, 0, 0, 0, 0);
			SelectObject(mDC, old);
		}
	}
	else
		spawnAnim.resource.Draw(mDC, pos.x - spawnAnim.size.right, pos.y - spawnAnim.size.bottom, spawnAnim.size.right * 2, spawnAnim.size.bottom * 2,
			(int)frame * spawnAnim.size.right, 0, spawnAnim.size.right, spawnAnim.size.bottom);
}

void Bombshe::handle_event()
{
	if (col) {
		if (attackable() && !targetLocked || (state == BDAMAGED && (int)frame == 1) && !targetLocked) {
			targetLocked = true;
			state = BATTACK;
			frame = 0;
		}
		if (targetLocked) {
			if (!isAttack && (int)frame == 4) {
				wave = new Effect(CEffect::BOMBSHE1, col->pos);
				EffectManager::getInstance()->set_effect(wave);
				isAttack = true;
			}
			if (isAttack) {
				attack();
				if ((int)(wave->time + 1) == wave->effect[wave->type].frame) {
					if (wave->effect[wave->type].frame == 13) {
						wave->type = CEffect::BOMBSHE2;
						wave->time = 0;
					}
					else if (wave->effect[wave->type].frame == 3)
						wave->time = 0;
				}
				if (state == BDAMAGED && (int)frame == 1) {
					state = BATTACK;
					frame = 0;
				}
			}
		}
	}
}

void Bombshe::update()
{
	if (col || HP <= 0) {
		frame = (frame + frame_time * animation[state][direction].velocity * animation[state][direction].frame);
		if (state == BIDLE) {
			if (frame >= animation[state][direction].frame) frame = 0;
			SetDirection();
			col->pos = pos;
		}
		else if (state == BATTACK && (int)frame < 5) {
			if (attackSize < 100)
				attackSize += 1;
			SetDirection();
			col->pos = pos;
		}
		else if (state == BDEAD) {
			if ((int)frame == animation[state][direction].frame) {
				int num = randrop(dre);
				if (num == 0) {
					drops.emplace_back(new DropItem(DROP::DROCKET, pos));
				}
				EnemyManager::getInstance()->delete_enemy(this);
				deleteSet.insert(this);
				EffectManager::getInstance()->set_effect(new Effect(CEffect::BOMBSHEDIE, pos));
			}
		}
		if ((int)frame == animation[state][direction].frame && state != BDAMAGED) frame = 0;
	}
	else {
		frame = (frame + frame_time * spawnAnim.velocity * spawnAnim.frame);
		if ((int)frame == spawnAnim.frame) {
			col = new Collider(Vector2D<float>(animation[STATE_IDLE][FRONT].size.right, animation[STATE_IDLE][FRONT].size.bottom));
			col->owner = this;
			col->layer = enemy;
			col->pos = pos;
			col->damage = 5;
			COLL.emplace_back(col);
			frame = 0;
		}
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
		direction = FRONT_LEFT;
	}
	else if (angle >= -120 && angle <= -60) {
		direction = FRONT;
	}
	else if (angle >= -60 && angle < -20) {
		direction = FRONT_RIGHT;
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

void Bombshe::handle_collision(int otherLayer, int damage)
{
	switch (otherLayer)
	{
	case wall:
	case water:
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
		pos -= (target->GetPos() - pos).Normalize() * 5;
		break;
	case player:
	case damaged_player:
		if (!isWallCollision(Vector2D<float>(lastPos.x, lastPos.y), col->size))
			pos = lastPos;
		break;
	case playerMelee:
		if (col == nullptr)return;
		EffectManager::getInstance()->set_effect(new Effect(CEffect::SWORDATTACK, col->pos));
		HP -= damage;
		if (HP <= 0) {
			state = BDEAD;
			for (auto i = COLL.begin(); i != COLL.end(); ++i)
				if (COLL[i - COLL.begin()] == this->col)
				{
					COLL.erase(i);
					break;
				}
			delete this->col;
			this->col = nullptr;
			if (wave)
				wave->time = wave->effect[wave->type].frame;
			SoundManager::getInstance()->play(ENEMYDEATH);
		}
		else {
			state = BDAMAGED;
			SoundManager::getInstance()->play(ENEMYHURT);
		}
		frame = 0;
		break;
	case playerBullet:
		if (col == nullptr)return;
		HP -= damage;
		if (HP <= 0) {
			state = BDEAD;
			for (auto i = COLL.begin(); i != COLL.end(); ++i)
				if (COLL[i - COLL.begin()] == this->col)
				{
					COLL.erase(i);
					break;
				}
			delete this->col;
			this->col = nullptr;
			if (wave)
				wave->time = wave->effect[wave->type].frame;
			SoundManager::getInstance()->play(ENEMYDEATH);
		}
		else {
			state = BDAMAGED;
			SoundManager::getInstance()->play(ENEMYHURT);
		}
		frame = 0;
		break;
	default:
		break;
	}
}

void Bombshe::CalWeight()
{
}

