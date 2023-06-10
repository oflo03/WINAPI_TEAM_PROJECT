#include "LogoState.h"
#include "PlayState.h"

extern HDC mDC;
extern RECT screen;

float enterTime;
bool entering;

LogoState::LogoState() :GameState()
{
	tuk.Load(L"main_tuk.png");
	logo.Load(L"main_logo.png");
	title.Load(L"main_title.png");
	logoTime = 0;
}

LogoState::~LogoState()
{
	tuk.Destroy();
	logo.Destroy();
	title.Destroy();
}

void LogoState::update()
{
	logoTime += 0.01;
	if (entering)
		if (logoTime > enterTime)
			change_state(new PlayState());
}

void LogoState::handle_events()
{
	if (GetAsyncKeyState(VK_ESCAPE)) {
		PostQuitMessage(0);
		return;
	}
	else if (GetAsyncKeyState(VK_RETURN) & 1 && logoTime > 5 && !entering)
	{
		entering = true;
		enterTime = logoTime + 0.5;
	}
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
	else
	{
		LONG alpha;
		if (entering)
			alpha = 255 * (enterTime - logoTime) * 2;
		else
			alpha = 255 * (logoTime > 5 ? 1 : logoTime < 4.5 ? 0 : (logoTime - 4.5) * 2);
		title.AlphaBlend(mDC, 0, 0, screen.right, screen.bottom, 0, 0, 1920, 1080, RGB(alpha, alpha, alpha));
	}
}