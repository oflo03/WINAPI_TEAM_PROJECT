#include "BossScene.h"
#include"PlayState.h"
#include"Boss.h"
#include"Player.h"
#include"MapManager.h"
#include"SoundManager.h"

extern HDC mDC;
extern RECT screen;
extern Vector2D<float> camSize;

BossScene::BossScene()
{
	scene.Load(L"resources/cutScene.png");
	time = 0;
	rect = { screen.right,100,screen.right * 2 + 20,800 };
	camPos = Player::getInstance()->GetPos();
	SoundManager::getInstance()->stop(MainState);
	SoundManager::getInstance()->play(BOSS);
}

BossScene::~BossScene()
{
	camPos = Player::getInstance()->GetPos();
}

void BossScene::update()
{
	if ((camPos - Boss::getInstance()->pos).GetLenth() > 3)
		camPos += (Boss::getInstance()->pos - camPos).Normalize() * 3;
	else {
		if (rect.left > 0)
			OffsetRect(&rect, -70, 0);
		else
			time++;
	}
	SoundManager::getInstance()->update();
}

void BossScene::handle_events()
{
	if (time == 70)
		pop_state();
	if (time == 1)
	{
		SoundManager::getInstance()->play(BOSSSCENE);
	}
}

void BossScene::draw()
{
	HDC mapDC = CreateCompatibleDC(mDC);
	HBITMAP mapbitmap = CreateCompatibleBitmap(mDC, 1920, 1080);
	SelectObject(mapDC, mapbitmap);
	MapManager::getInstance()->PrintMap(mapDC);
	Player::getInstance()->draw_character(mapDC);
	Boss::getInstance()->draw(mapDC);
	StretchBlt(mDC, 0, 0, screen.right, screen.bottom,
		mapDC, camPos.x - camSize.x, camPos.y - camSize.y, camSize.x * 2, camSize.y * 2, SRCCOPY);
	scene.Draw(mDC, rect);
	DeleteObject(mapbitmap);
	DeleteDC(mapDC);
}
