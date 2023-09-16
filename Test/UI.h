#pragma once
#include "Player.h"

class UI
{
protected:
	static UI* instance;
	CImage heart, weapons, bossHp, bossHpFrame, bossHpFrame2;
	Player* pp;
	RECT ammoTextBox;
	HFONT romulus;
	TCHAR ammoText[8];
	UI();
	~UI();
public:
	static UI* getInstance();
	static void release();
	void draw(HDC mDC);
};