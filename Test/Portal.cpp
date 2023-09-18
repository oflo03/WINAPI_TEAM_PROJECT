#include"Portal.h"
#include"Player.h"
#include"LevelManager.h"

extern double frame_time;
extern Vector2D<float> camSize;

Portal* Portal::getInstance()
{
	if (instance == nullptr)
		instance = new Portal(0, 0);
	return instance;
}

void Portal::release()
{
	if (instance != nullptr)
		delete instance;
	instance = nullptr;
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
	if ((GetAsyncKeyState('E') & 0x8000) && (Player::getInstance()->GetPos() - pos).GetLenth() < 100)
		LevelManager::getInstance()->loadNextStage();
}

void Portal::Draw(HDC mDC)
{
	portal.resource.Draw(mDC, pos.x - portal.size.right, pos.y - portal.size.bottom - 50, portal.size.right * 2, portal.size.bottom * 2,
		(int)pframe * portal.size.right, 0, portal.size.right, portal.size.bottom);
	if (!(pos - camPos < camSize))
		P.resource.Draw(mDC, camPos.x + (pos - camPos).Normalize().x * camSize.x / 1.1 - P.size.right / 2,
			camPos.y + (pos - camPos).Normalize().y * camSize.y / 1.1 - P.size.bottom / 2, P.size.right, P.size.bottom,
			(int)eframe * P.size.right, 0, P.size.right, P.size.bottom);
	if ((camPos - pos).GetLenth() < 100)
		E.resource.Draw(mDC, Player::getInstance()->GetPos().x - E.size.right / 2, Player::getInstance()->GetPos().y - E.size.bottom - 30, E.size.right, E.size.bottom,
			(int)eframe * E.size.right, 0, E.size.right, E.size.bottom);
}


Portal* Portal::instance = nullptr;