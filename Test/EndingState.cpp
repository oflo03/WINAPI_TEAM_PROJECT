#include "EndingState.h"
#include "MenuState.h"
#include"SoundManager.h"

extern HDC mDC;
extern RECT screen;

EndingState::EndingState()
{
	back.Load(L"resources/Ending.png");
	rom = CreateFont(80, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"Romulus");
	SoundManager::getInstance()->play(END);
}

EndingState::~EndingState()
{
	back.Destroy();
	DeleteObject(rom);
	SoundManager::getInstance()->stop(END);
}

void EndingState::update()
{

}
void EndingState::handle_events()
{

	if (GetAsyncKeyState(VK_ESCAPE) & 1) {
		end_game();
		push_state(new MenuState);
	}
}
void EndingState::draw()
{
	back.Draw(mDC, 0, 0, screen.right, screen.bottom);
	SelectObject(mDC, rom);
	SetBkMode(mDC, TRANSPARENT);
	SetTextColor(mDC, RGB(255, 255, 255));
	back.Draw(mDC, 470, 120);
	TCHAR CT1[] = L"Press ESC";
	TextOut(mDC, 600, screen.bottom - 220, CT1, 9);
}