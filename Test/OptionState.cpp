#include "OptionState.h"
#include"MenuState.h"
#include"SoundManager.h"
#include"PlayState.h"
#include"EnemyManager.h"
#include"EffectManager.h"
#include"Player.h"
#include"DropItem.h"
#include"Boss.h"
#include"Portal.h"
#include"MapManager.h"
#include"LevelManager.h"

extern std::vector<GameState*> stateStack;
extern HDC mDC;
extern CImage cursor;
extern RECT screen;
extern double volume;
extern POINT mPoint;

OptionState::OptionState() : string1(L"*menu"),string2(L"*control"),string3(L"*continue")
{
	black.Load(L"resources/black.png");
	background.Load(L"resources/OPTION.png");
	control.Load(L"resources/control.png");
	font = CreateFont(screen.right/25, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"Romulus");
	rect[0] = {320,570,520,620};
	rect[1] = {600,570,860,620};
	rect[2] = {920,570,1250,620};
	for (int i = 0; i < 3; i++)
		isOn[i] = false;
	controlOn = false;
}

OptionState::~OptionState()
{
	black.Destroy();
	background.Destroy();
	control.Destroy();
	DeleteObject(font);
}

void OptionState::update()
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

void OptionState::handle_events()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 1) {
		if (controlOn)
			controlOn = false;
		else
			pop_state();
	}
	else if (GetAsyncKeyState(VK_LBUTTON)&&!controlOn) {
		RECT temp = { 690, 378, 1110,420 };
		RECT temp2 = { (700 + 200 * volume) - 6, 368, (700 + 200 * volume) + 6, 420 };
		if (isOn[0]) {
			SoundManager::getInstance()->play(BUTTONCLICK);
			end_game();
			push_state(new MenuState);
		}
		else if (isOn[1]) {
			SoundManager::getInstance()->stop(CURSORON);
			if (!SoundManager::getInstance()->isPlaying(BUTTONCLICK)) {
				SoundManager::getInstance()->play(BUTTONCLICK);
			}
			controlOn = true;
		}
		else if (isOn[2]) {
			SoundManager::getInstance()->play(BUTTONCLICK);
			pop_state();
		}
		else if ((PtInRect(&temp, mPoint) || PtInRect(&temp2, mPoint))&& mPoint.x>= temp.left) {
			volume = (mPoint.x - temp.left) / 200.0;
			SoundManager::getInstance()->volumeSet(volume);
		}
	}
}

void OptionState::draw()
{
	(*(stateStack.end()-2))->draw();
	black.AlphaBlend(mDC, 0, 0, screen.right, screen.bottom, 0, 0, black.GetWidth(), black.GetHeight(), 130);
	background.Draw(mDC, 200, 200, screen.right - 400, screen.bottom - 400, 0, 0, background.GetWidth(), background.GetHeight());
	SelectObject(mDC, font);
	SetBkMode(mDC, TRANSPARENT);
	SetTextColor(mDC, RGB(255, 255, 255));
	TextOut(mDC, 650, 340, L"-", 1);
	TextOut(mDC, 1120, 347, L"+", 1);
	if (isOn[0]) {
		SetTextColor(mDC, RGB(255, 186, 0));
	}
	else 
		SetTextColor(mDC, RGB(255, 255, 255));
	DrawText(mDC, string1, 5, &rect[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	if (isOn[1]) {
		SetTextColor(mDC, RGB(255, 186, 0));
	}
	else
		SetTextColor(mDC, RGB(255, 255, 255));
	DrawText(mDC, string2, 8, &rect[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	if (isOn[2]) {
		SetTextColor(mDC, RGB(255, 186, 0));
	}
	else
		SetTextColor(mDC, RGB(255, 255, 255));
	DrawText(mDC, string3, 9, &rect[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	HBRUSH bar = CreateSolidBrush(RGB(125, 125, 125));
	HBRUSH brush= (HBRUSH)SelectObject(mDC, bar);
	Rectangle(mDC, 700, 380, 1100,390);
	DeleteObject(bar);
	SelectObject(mDC, brush);
	Rectangle(mDC, 700, 378, 700+200*volume, 392);
	Rectangle(mDC, (700 + 200 * volume)-6, 368, (700 + 200 * volume)+6, 402);
	if (controlOn)
		control.Draw(mDC, 200, 100, screen.right - 400, screen.bottom - 200, 0, 0, control.GetWidth(), control.GetHeight());
	cursor.Draw(mDC, mPoint.x - 20, mPoint.y - 30, 40, 40);
}
