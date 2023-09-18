#include "BossDieScene.h"
#include"MapManager.h"
#include"EffectManager.h"
#include"SoundManager.h"

extern HDC mDC;
extern RECT screen;
extern Vector2D<float> camSize;

BossDieScene::BossDieScene() : boss(Boss::getInstance()), player(Player::getInstance()), time(0),dir(0)
{
	r1 = { 0,-200,screen.right,0 };
	r2 = { 0,screen.bottom,screen.right,screen.bottom+200 };
	EffectManager::getInstance()->set_effect(new Effect(BOSSHIT, boss->pos));
	SoundManager::getInstance()->stop(BOSS);
	rom = CreateFont(50, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"dalmoori");
}

BossDieScene::~BossDieScene()
{
	camPos = player->GetPos();
	DeleteObject(rom);
}

void BossDieScene::update()
{
	if (time <= 100) {
		double range = (dir % 2 == 0) ? (150.0 / time) : -(150.0 / time);
		camPos.x = player->GetPos().x + range;
		if(time % 5 == 0)
			dir++;
		time++;
	}
	else if (time >= 100) {
		if((camPos - boss->pos).GetLenth() > 4)
			camPos += (boss->pos - camPos).Normalize() * 4;
		else if((camPos - boss->pos).GetLenth() <= 4&&(camPos - boss->pos).GetLenth() > 2)
			camPos += (boss->pos - camPos).Normalize();
	}
	if((camPos - boss->pos).GetLenth() < 2){
		if (r1.top < 0) {
			OffsetRect(&r1, 0, 20);
			OffsetRect(&r2, 0, -20);
		}
		boss->update();
		time++;
	}

	EffectManager::getInstance()->update();
	EffectManager::getInstance()->delete_effect();
	SoundManager::getInstance()->update();
}

void BossDieScene::handle_events()
{
	boss->handle_event();
	if(time==420)
		pop_state();
}

void BossDieScene::draw()
{
	HDC mapDC = CreateCompatibleDC(mDC);
	HBITMAP mapbitmap = CreateCompatibleBitmap(mDC, 1920, 1080);
	SelectObject(mapDC, mapbitmap);
	SelectObject(mDC, rom);
	MapManager::getInstance()->PrintMap(mapDC);
	player->draw_character(mapDC);
	if(time<=380)
		boss->draw(mapDC);
	EffectManager::getInstance()->Draw(mapDC);
	StretchBlt(mDC, 0, 0, screen.right, screen.bottom,
		mapDC, camPos.x - camSize.x, camPos.y - camSize.y, camSize.x * 2, camSize.y * 2, SRCCOPY);
	FillRect(mDC, &r1, (HBRUSH)GetStockObject(BLACK_BRUSH));
	FillRect(mDC, &r2, (HBRUSH)GetStockObject(BLACK_BRUSH));
	SetBkMode(mDC, TRANSPARENT);
	SetTextColor(mDC, RGB(255, 255, 255));
	if (time>=150&&time<=350) {
		TCHAR CT1[] = L"Å©À¹..! ¿À´ÃÀº ÀÌÂë¿¡¼­ ¹°·¯³ªÁÖÁö...";
		TextOut(mDC, 350, screen.bottom - 130, CT1, 23);
	}
	DeleteObject(mapbitmap);
	DeleteDC(mapDC);
}
