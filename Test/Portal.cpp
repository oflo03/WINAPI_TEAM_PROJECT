#include"Portal.h"
#include"Player.h"

extern double frame_time;

Portal* Portal::getInstance()
{
	if (instance == nullptr)
		instance = new Portal(960, 540);
	return instance;
}

void Portal::update()
{
	pframe = pframe + frame_time * portal.velocity * portal.frame;
	if (pframe >= portal.frame)pframe = 0;
	eframe = eframe + frame_time * E.velocity * E.frame;
	if (eframe >= E.frame)eframe = 0;
}

void Portal::handle_event()
{
	if ((GetAsyncKeyState('E') & 1) && (Player::getInstance()->GetPos() - pos).GetLenth() < 100)
		; //여기에 다음 스테이지로 추가
}

void Portal::Draw(HDC mDC)
{
	portal.resource.Draw(mDC, pos.x - portal.size.right, pos.y - portal.size.bottom - 50, portal.size.right * 2, portal.size.bottom * 2,
		(int)pframe * portal.size.right, 0, portal.size.right, portal.size.bottom);
	if ((Player::getInstance()->GetPos() - pos).GetLenth() < 100)
		E.resource.Draw(mDC, Player::getInstance()->GetPos().x - E.size.right / 2, Player::getInstance()->GetPos().y - E.size.bottom - 30, E.size.right, E.size.bottom,
			(int)eframe * E.size.right, 0, E.size.right, E.size.bottom);
}


Portal* Portal::instance = nullptr;