#include "UI.h"
#include"LevelManager.h"
#include"Boss.h"
#define HeartSize 90

CImage heart, weapons, cursor, bossHp, bossHpFrame, bossHpFrame2;
Player* pp;

RECT ammoTextBox;
HFONT romulus;
TCHAR ammoText[8];

void UI::init()
{
	heart.Load(L"UI_Image_Heart.png");
	weapons.Load(L"UI_Image_Weapons.png");
	cursor.Load(L"UI_Image_Cursor.png");
	bossHp.Load(L"boss_hp.png");
	bossHpFrame.Load(L"boss_hp_frame.png");
	bossHpFrame2.Load(L"boss_hp_frame2.png");
	pp = Player::getInstance();
	ammoTextBox = RECT(monitorSize.x - 250, 170, monitorSize.x - 10, 200);
	romulus = CreateFont(48, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"Romulus");
}

void UI::Destroy()
{
	heart.Destroy();
	weapons.Destroy();
	cursor.Destroy();
	bossHp.Destroy();
	bossHpFrame.Destroy();
	bossHpFrame2.Destroy();
	DeleteObject(romulus);
}

void UI::draw(HDC mDC)
{
	int hp = pp->GetHP();
	for (int i = 0; i < hp / 2; ++i)
		heart.Draw(mDC, 10 + i * HeartSize, 10, HeartSize, HeartSize, 0, 0, 15, 15);
	if (hp % 2)
		heart.Draw(mDC, 10 + hp / 2 * HeartSize, 10, HeartSize, HeartSize, 15, 0, 15, 15);
	weapons.AlphaBlend(mDC, monitorSize.x - 250, 10, 240, 160, 0, 0, 48, 32, RGB(200, 200, 200));
	weapons.Draw(mDC, monitorSize.x - 250, 10, 240, 160, 48 + pp->GetWeapon() * 48, 0, 48, 32);

	SelectObject(mDC, romulus);
	SetBkMode(mDC, TRANSPARENT);
	SetTextColor(mDC, RGB(255, 255, 255));
	if (pp->GetWeapon())
		swprintf_s(ammoText, 8, L"%2d / %2d", pp->GetWeaponCurAmmo(), pp->GetWeaponMaxAmmo());
	else
		swprintf_s(ammoText, 8, L" ¡Ä / ¡Ä ");
	DrawText(mDC, ammoText, 7, &ammoTextBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	if (LevelManager::getInstance()->GetStage() == 4) {
		if (Boss::getInstance()->getHP() > 0) {
			float decreased = 1.0f - (float)Boss::getInstance()->getHP() / BOSSHP;
			int srclenth = (decreased * (bossHp.GetWidth() - 2)) / 2;
			int destlenth = (decreased * (monitorSize.x - 600)) / 2;
			bossHp.Draw(mDC, 300 + destlenth, monitorSize.y - 100, monitorSize.x - 600 - destlenth * 2, 90, srclenth, 0, bossHp.GetWidth() - srclenth * 2, bossHp.GetHeight());
		}
		bossHpFrame.Draw(mDC, 300, monitorSize.y - 100, monitorSize.x - 600, 90, 0, 0, bossHpFrame.GetWidth(), bossHp.GetHeight());
		bossHpFrame2.Draw(mDC, 300, monitorSize.y - 100, monitorSize.x - 600, 90, 0, 0, bossHpFrame.GetWidth(), bossHp.GetHeight());
	}
	POINT mPos;
	GetCursorPos(&mPos);
	cursor.Draw(mDC, mPos.x - 20, mPos.y - 30, 40, 40);
}