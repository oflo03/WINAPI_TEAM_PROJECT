#include "UI.h"

#define HeartSize 90

CImage heart, weapons, cursor;
Player* pp;
RECT ammoTextBox;
HFONT romulus;
TCHAR ammoText[8];

void UI::init()
{
	heart.Load(L"UI_Image_Heart.png");
	weapons.Load(L"UI_Image_Weapons.png");
	cursor.Load(L"UI_Image_Cursor.png");
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

	POINT mPos;
	GetCursorPos(&mPos);
	cursor.Draw(mDC, mPos.x - 20, mPos.y - 30, 40, 40);
}