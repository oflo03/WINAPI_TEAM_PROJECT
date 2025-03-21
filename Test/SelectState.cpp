#include "SelectState.h"
#include"MenuState.h"
#include "PlayState.h"
#include "Player.h"
#include"SoundManager.h"

#define imagesize 2
extern HDC mDC;
extern RECT screen;
extern CImage cursor;
extern POINT mPoint;

RECT BT1, BT2;
RECT TB1, TB2, TB3, TB4;
HFONT rom;
TCHAR CT1[] = L"GET MORE HP";
TCHAR CT2[] = L"SWORD REFLETS BULLET";

SelectState::SelectState()
{
	Player::release();
	background.Load(L"resources/main_selchar_back.png");
	image1.Load(L"resources/marin_front.png");
	image2.Load(L"resources/knight_front.png");
	BT1 = RECT(screen.right / 4 - image1.GetWidth() * imagesize, screen.bottom / 2 - image1.GetHeight() * imagesize,
		screen.right / 4 + image1.GetWidth() * imagesize, screen.bottom / 2 + image1.GetHeight() * imagesize);
	BT2 = RECT(screen.right / 4 * 3 - image2.GetWidth() * imagesize, screen.bottom / 2 - image2.GetHeight() * imagesize,
		screen.right / 4 * 3 + image2.GetWidth() * imagesize, screen.bottom / 2 + image2.GetHeight() * imagesize);
	TB1 = RECT(BT1.left - 150, BT1.top - 40, BT1.right + 150, BT1.top);
	TB2 = RECT(BT2.left - 150, BT2.top - 40, BT2.right + 150, BT2.top);
	TB3 = RECT(BT1.left - 150, BT1.bottom, BT1.right + 150, BT1.bottom + 40);
	TB4 = RECT(BT2.left - 150, BT2.bottom, BT2.right + 150, BT2.bottom + 40);

	rom = CreateFont(48, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"Romulus");
	mouseOn[0] = mouseOn[1] = false;
	SoundManager::getInstance()->play(SELECTSTATE);
}

SelectState::~SelectState()
{
	background.Destroy();
	image1.Destroy();
	image2.Destroy();
	DeleteObject(rom);
	SoundManager::getInstance()->stop(SELECTSTATE);
}

void SelectState::update()
{
	SoundManager::getInstance()->update();
}

void SelectState::handle_events()
{
	if (PtInRect(&BT1, mPoint)) {
		if (mouseOn[0] == false) {
			SoundManager::getInstance()->play(CURSORON);
			mouseOn[0] = true;
		}
	}
	else if (!PtInRect(&BT1, mPoint)) {
		mouseOn[0] = false;
	}
	if (PtInRect(&BT2, mPoint)) {
		if (mouseOn[1] == false) {
			SoundManager::getInstance()->play(CURSORON);
			mouseOn[1] = true;
		}
	}
	else if (!PtInRect(&BT2, mPoint)) {
		mouseOn[1] = false;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 1) {
		change_state(new MenuState());
		return;
	}
	else if (GetAsyncKeyState(VK_LBUTTON) & 1) {
		if (mPoint.x >= BT1.left && mPoint.x <= BT1.right && mPoint.y >= BT1.top && mPoint.y <= BT1.bottom) {
			selectedPlayer = marin;
			SoundManager::getInstance()->play(BUTTONCLICK);
			change_state(new PlayState());
		}
		else if (mPoint.x >= BT2.left && mPoint.x <= BT2.right && mPoint.y >= BT2.top && mPoint.y <= BT2.bottom) {
			selectedPlayer = knight;
			SoundManager::getInstance()->play(BUTTONCLICK);
			change_state(new PlayState());
		}
	}
}

void SelectState::draw()
{
	background.AlphaBlend(mDC, 0, 0, screen.right, screen.bottom, 0, 0, 1920, 1080, RGB(30, 30, 30));

	SelectObject(mDC, rom);
	SetBkMode(mDC, TRANSPARENT);
	SetTextColor(mDC, RGB(255, 255, 255));
	DrawText(mDC, L"MARIN", 5, &TB1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	if (mPoint.x >= BT1.left && mPoint.x <= BT1.right && mPoint.y >= BT1.top && mPoint.y <= BT1.bottom) {
		image1.AlphaBlend(mDC, BT1.left, BT1.top, BT1.right - BT1.left, BT1.bottom - BT1.top,
			0, 0, image1.GetWidth(), image1.GetHeight(), RGB(255, 255, 255));
		DrawText(mDC, CT1, 11, &TB3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else image1.AlphaBlend(mDC, BT1.left, BT1.top, BT1.right - BT1.left, BT1.bottom - BT1.top,
		0, 0, image1.GetWidth(), image1.GetHeight(), RGB(150, 150, 150));

	DrawText(mDC, L"KNIGHT", 6, &TB2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	if (mPoint.x >= BT2.left && mPoint.x <= BT2.right && mPoint.y >= BT2.top && mPoint.y <= BT2.bottom) {
		image2.AlphaBlend(mDC, BT2.left, BT2.top, BT2.right - BT2.left, BT2.bottom - BT2.top,
			0, 0, image2.GetWidth(), image2.GetHeight(), RGB(255, 255, 255));
		DrawText(mDC, CT2, 20, &TB4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else image2.AlphaBlend(mDC, BT2.left, BT2.top, BT2.right - BT2.left, BT2.bottom - BT2.top,
		0, 0, image2.GetWidth(), image2.GetHeight(), RGB(150, 150, 150));
	cursor.Draw(mDC, mPoint.x - 20, mPoint.y - 30, 40, 40);
}
