#include "GameOverState.h"
#include "SelectState.h"
#include"Player.h"

extern HDC mDC;
extern RECT screen;
extern Vector2D<float> camSize;

GameOverState::GameOverState()
{
	back.Load(L"resources/GameOver.png");
}

GameOverState::~GameOverState()
{
	back.Destroy();
}

void GameOverState::update()
{
	Player::getInstance()->update();
	if ((camPos - Player::getInstance()->GetPos()).GetLenth() > 3)
		camPos += (Player::getInstance()->GetPos() - camPos).Normalize()*3;
}
void GameOverState::handle_events()
{
	if (GetAsyncKeyState(VK_ESCAPE)&1) {
		change_state(new SelectState);
	}
}
void GameOverState::draw()
{
	HDC mapDC = CreateCompatibleDC(mDC);
	HBITMAP mapbitmap = CreateCompatibleBitmap(mDC, 1920, 1080);
	SelectObject(mapDC, mapbitmap);
	Player::getInstance()->draw_character(mapDC);
	StretchBlt(mDC, 0, 0, screen.right, screen.bottom,
		mapDC, camPos.x - camSize.x, camPos.y - camSize.y, camSize.x * 2, camSize.y * 2, SRCCOPY);
	back.Draw(mDC, 370, 120);
	DeleteObject(mapbitmap);
	DeleteDC(mapDC);
	//back.Draw(mDC, 0, 0, screen.right, screen.bottom);
}