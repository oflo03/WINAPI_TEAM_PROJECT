#include "Boss.h"
#include"BossIdle.h"

Boss* Boss::instance = nullptr;

Boss::Boss() {
	body.resource.Load(L"boss_body.png");
	body.frame = 3;
	body.size = { 0,0,body.resource.GetWidth() / body.frame ,body.resource.GetHeight() };
	hand[LEFT].resource.Load(L"boss_lefthand.png");
	hand[LEFT].frame = 2;
	hand[LEFT].size= { 0,0,hand[0].resource.GetWidth() / hand[0].frame ,hand[0].resource.GetHeight() };
	hand[RIGHT].resource.Load(L"boss_righthand.png");
	hand[RIGHT].frame = 2;
	hand[RIGHT].size = { 0,0,hand[1].resource.GetWidth() / hand[1].frame ,hand[1].resource.GetHeight() };
	shadow.Load(L"shadow.png");
	state = new BossIdle();
	frame = 0;
	target = Player::getInstance(1);
	pos.x = 900;
	pos.y = 500;
	HP = 1000;
	handType[LEFT] = 1;
	handType[RIGHT] = 0;
	for (int i = 0; i < 2; i++)
		angle[i] = 0;
	handPos[0].x = pos.x - 30;
	handPos[0].y = pos.y - 10;
	handPos[1].x = pos.x + 30;
	handPos[1].y = pos.y - 10;

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
	return nullptr;
}

void Boss::release()
{
}

void Boss::draw(HDC mDC)
{
	shadow.Draw(mDC, pos.x - shadow.GetWidth()*2, pos.y + body.size.bottom- 2 - shadow.GetHeight()*2, shadow.GetWidth() * 4, shadow.GetHeight() * 4);
	body.resource.Draw(mDC, pos.x - body.size.right, pos.y - body.size.bottom, body.size.right * 2, body.size.bottom * 2, body.size.right * frame, 0, body.size.right, body.size.bottom);
	for (int i = 0; i < 2; i++)
		hand[i].resource.Draw(mDC, handPos[i].x - hand[i].size.right, handPos[i].y - hand[i].size.bottom, hand[i].size.right * 2, hand[i].size.bottom * 2, hand[i].size.right * handType[i], 0, hand[i].size.right, hand[i].size.bottom);
}

void Boss::handle_event()
{
}

void Boss::update()
{
}

void Boss::handle_collision(int otherLayer, int damage)
{
}
