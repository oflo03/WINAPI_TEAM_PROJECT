#include "GameOverState.h"
#include "MenuState.h"
#include"MapManager.h"
#include"Player.h"

extern HDC mDC;
extern RECT screen;
extern Vector2D<float> camSize;

GameOverState::GameOverState()
{
	time = 0;
	dir = 0;
	back.Load(L"resources/GameOver.png");
	black.Load(L"resources/black.png");
	rom = CreateFont(80, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"Romulus");
}

GameOverState::~GameOverState()
{
	back.Destroy();
	black.Destroy();
	DeleteObject(rom);
}

void GameOverState::update()
{
	Player::getInstance()->update();
	if (time <= 100) {
		double range = (dir % 2 == 0) ? (100.0 / time) : -(100.0 / time);
		camPos.x = Player::getInstance()->GetPos().x + range;
		if (time % 10 == 0)
			dir++;
		time++;
	}
	else if (time >= 100) {
		if ((camPos - Player::getInstance()->GetPos()).GetLenth() > 3)
			camPos += (Player::getInstance()->GetPos() - camPos).Normalize() * 2;
		else
			time++;
	}
}
void GameOverState::handle_events()
{
	if (GetAsyncKeyState(VK_ESCAPE)&1) {
		end_game();
		push_state(new MenuState);
	}
}
void GameOverState::draw()
{
	HDC mapDC = CreateCompatibleDC(mDC);
	HBITMAP mapbitmap = CreateCompatibleBitmap(mDC, 1920, 1080);
	SelectObject(mapDC, mapbitmap);
	MapManager::getInstance()->PrintMap(mapDC);
	Player::getInstance()->draw_character(mapDC);
	StretchBlt(mDC, 0, 0, screen.right, screen.bottom,
		mapDC, camPos.x - camSize.x, camPos.y - camSize.y, camSize.x * 2, camSize.y * 2, SRCCOPY);
	static LONG alpha = 0;
	if (time > 101) {
		if (alpha < 255) alpha += 5;
		black.AlphaBlend(mDC, 0, 0, screen.right, screen.bottom, 0, 0, black.GetWidth(), black.GetHeight(), alpha);
	}
	if (alpha >= 255) {
		SelectObject(mDC, rom);
		SetBkMode(mDC, TRANSPARENT);
		SetTextColor(mDC, RGB(255, 255, 255));
		back.Draw(mDC, 470, 120);
		TCHAR CT1[] = L"Press ESC";
		TextOut(mDC, 400, screen.bottom - 120, CT1, 9);
	}
	DeleteObject(mapbitmap);
	DeleteDC(mapDC);
}