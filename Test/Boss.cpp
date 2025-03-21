#include "Boss.h"
#include"BossIdle.h"
#include"EffectManager.h"

Boss* Boss::instance = nullptr;

Boss::Boss() {
	body.resource.Load(L"resources/boss_body.png");
	body.frame = 5;
	body.size = { 0,0,body.resource.GetWidth() / body.frame ,body.resource.GetHeight() };
	hand[LEFT].resource.Load(L"resources/boss_lefthand.png");
	hand[LEFT].frame = 5;
	hand[LEFT].size= { 0,0,hand[0].resource.GetWidth() / hand[0].frame ,hand[0].resource.GetHeight() };
	hand[RIGHT].resource.Load(L"resources/boss_righthand.png");
	hand[RIGHT].frame = 5;
	hand[RIGHT].size = { 0,0,hand[1].resource.GetWidth() / hand[1].frame ,hand[1].resource.GetHeight() };
	shadow.Load(L"resources/shadow.png");
	state = new BossIdle();
	pattern.push_back(3);
	pattern.push_back(2);
	pattern.push_back(1);
	pattern.push_back(0);
	frame = 0;
	target = Player::getInstance();
	pos.x = 960;
	pos.y = 500;
	lastPattern = 2;
	handType[LEFT] = 1;
	handType[RIGHT] = 0;
	for (int i = 0; i < 2; i++)
		angle[i] = 0;
	handPos[0].x = pos.x - 60;
	handPos[0].y = pos.y - 10;
	handPos[1].x = pos.x + 60;
	handPos[1].y = pos.y - 10;
	col = new Collider(body.size.right - 50);
	col->owner = this;
	col->layer = enemy;
	col->pos = pos;
	col->damage = 5;
	COLL.emplace_back(col);
}

Boss::~Boss()
{
	body.resource.Destroy();
	hand[0].resource.Destroy();
	hand[1].resource.Destroy();
	shadow.Destroy();
}

Boss* Boss::getInstance()
{
	if (instance == nullptr)
		instance = new Boss();
	return instance;
}

void Boss::release()
{
	if (instance != nullptr)
		delete instance;
	instance = nullptr;
}

void Boss::draw(HDC mDC)
{
	shadow.Draw(mDC, 960 - shadow.GetWidth()*2, 500 + body.size.bottom- 2 - shadow.GetHeight()*2, shadow.GetWidth() * 4, shadow.GetHeight() * 4);
	body.resource.Draw(mDC, pos.x - body.size.right, pos.y - body.size.bottom, body.size.right * 2, body.size.bottom * 2, body.size.right * frame, 0, body.size.right, body.size.bottom);
	for (int i = 0; i < 2; i++)
		hand[i].resource.Draw(mDC, handPos[i].x - hand[i].size.right, handPos[i].y - hand[i].size.bottom, hand[i].size.right * 2, hand[i].size.bottom * 2, hand[i].size.right * handType[i], 0, hand[i].size.right, hand[i].size.bottom);
}

void Boss::handle_event()
{
	BossState* temp = this->state->handle_event(*this);
	if (temp != nullptr) {
		delete this->state;
		this->state = temp;
		this->state->enter(*this);
	}
}

void Boss::update()
{
	state->update(*this);
	if(col!=nullptr)
		col->pos = pos;
}

void Boss::handle_collision(int otherLayer, int damage)
{
	switch (otherLayer)
	{
	case playerMelee:
		EffectManager::getInstance()->set_effect(new Effect(CEffect::SWORDATTACK, col->pos));
		HP -= damage;
		if (HP <= 0) {
			for (auto i = COLL.begin(); i != COLL.end(); ++i)
				if (COLL[i - COLL.begin()] == this->col)
				{
					COLL.erase(i);
					break;
				}
			delete this->col;
			this->col = nullptr;
		}
		break;
	case playerBullet:
		HP -= damage;
		if (HP <= 0) {
			for (auto i = COLL.begin(); i != COLL.end(); ++i)
				if (COLL[i - COLL.begin()] == this->col)
				{
					COLL.erase(i);
					break;
				}
			delete this->col;
			this->col = nullptr;
		}
		break;
	default:
		break;
	}
}
