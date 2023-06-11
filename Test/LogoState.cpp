#include "LogoState.h"
#include "MenuState.h"

extern HDC mDC;
extern RECT screen;

float enterTime;
bool entering;

LogoState::LogoState() :GameState()
{
	tuk.Load(L"main_tuk.png");
	logo.Load(L"main_logo.png");
	logoTime = 0;
}

LogoState::~LogoState()
{
	tuk.Destroy();
	logo.Destroy();
}

void LogoState::update()
{
	logoTime += 0.01;
}

void LogoState::handle_events()
{
	if (GetAsyncKeyState(VK_ESCAPE)) {
		PostQuitMessage(0);
		return;
	}
	else if (GetAsyncKeyState('E') & 1)
	{
		if (logoTime < 1.5)
			logoTime = 1.5;
		else if (logoTime >= 1.5 && logoTime < 2)
			logoTime = 2;
		else if (logoTime >= 2 && logoTime < 3.5)
			logoTime = 3.5;
		else if (logoTime >= 3.5 && logoTime < 4)
			logoTime = 4;
	}
	else if (logoTime >= 4)
		change_state(new MenuState);
}


void LogoState::draw()
{
	if (logoTime < 2) {
		LONG alpha = 255 * (logoTime < 0.5 ? logoTime * 2 : logoTime < 1.5 ? 1 : (logoTime - 2) * -2);
		tuk.AlphaBlend(mDC, 0, 0, screen.right, screen.bottom, 0, 0, 1920, 1080, RGB(alpha, alpha, alpha));
	}
	else if (logoTime < 4) {
		LONG alpha = 255 * (logoTime < 2.5 ? (logoTime - 2) * 2 : logoTime < 3.5 ? 1 : (logoTime - 4) * -2);
		logo.AlphaBlend(mDC, 0, 0, screen.right, screen.bottom, 0, 0, 1920, 1080, RGB(alpha, alpha, alpha));
	}
}