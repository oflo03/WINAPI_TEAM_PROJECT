#include "MenuState.h"
#include "SelectState.h"
#include"OptionState.h"
#include"SoundManager.h"

extern HDC mDC;
extern RECT screen;
extern CImage cursor;
extern POINT mPoint;

MenuState::MenuState() : string1(L"PLAY"), string2(L"OPTIONS"), string3(L"QUIT")
{
	title.Load(L"resources/main_title.png");
	font = CreateFont(60, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"Romulus");
	rect[0] = { 20,610,180,670 };
	rect[1] = { 20,690,220,750 };
	rect[2] = { 20,770,160,830 };
	for (int i = 0; i < 3; i++)
		isOn[i] = false;
	SoundManager::getInstance()->play(TitleState);
}
MenuState::~MenuState()
{
	title.Destroy();
	DeleteObject(font);
	SoundManager::getInstance()->stop(TitleState);
}

void MenuState::update()
{
	SoundManager::getInstance()->update();
	for (int i = 0; i < 3; i++) {
		if (PtInRect(&rect[i], mPoint)) {
			if (!isOn[i])
				SoundManager::getInstance()->play(CURSORON);
			isOn[i] = true;
		}
		else isOn[i] = false;
	}
}

void MenuState::handle_events()
{
	if (GetAsyncKeyState(VK_LBUTTON)&1) {
		if (isOn[0]) {
			SoundManager::getInstance()->play(BUTTONCLICK);
			change_state(new SelectState);
		}
		else if (isOn[1]) {
			SoundManager::getInstance()->play(BUTTONCLICK);
			push_state(new OptionState);
		}
		else if (isOn[2]) {
			SoundManager::getInstance()->play(BUTTONCLICK);
			PostQuitMessage(0);
			return;
		}
	}
}

void MenuState::draw()
{
	title.Draw(mDC, 0, 0, screen.right, screen.bottom, 0, 0, 1920, 1080);
	SelectObject(mDC, font);
	SetBkMode(mDC, TRANSPARENT);
	SetTextColor(mDC, RGB(255, 255, 255));
	if (isOn[0]) {
		SetTextColor(mDC, RGB(255, 186, 0));
	}
	else
		SetTextColor(mDC, RGB(255, 255, 255));
	DrawText(mDC, string1, 5, &rect[0],  DT_VCENTER | DT_SINGLELINE);
	if (isOn[1]) {
		SetTextColor(mDC, RGB(255, 186, 0));
	}
	else
		SetTextColor(mDC, RGB(255, 255, 255));
	DrawText(mDC, string2, 8, &rect[1],  DT_VCENTER | DT_SINGLELINE);
	if (isOn[2]) {
		SetTextColor(mDC, RGB(255, 186, 0));
	}
	else
		SetTextColor(mDC, RGB(255, 255, 255));
	DrawText(mDC, string3, 9, &rect[2],  DT_VCENTER | DT_SINGLELINE);
	cursor.Draw(mDC, mPoint.x - 20, mPoint.y - 30, 40, 40);
}
