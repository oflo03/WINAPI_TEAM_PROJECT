#include "LogoState.h"
#include "PlayState.h"

extern HDC mDC;
extern RECT screen;

LogoState::LogoState() :GameState()
{
	logo.Load(L"main_logo.png");
	logoTime = 0;
}

LogoState::~LogoState()
{
	logo.Destroy();
}

void LogoState::update()
{
	if (logoTime > 1.0) {
		logoTime = 0;
		change_state(new PlayState());
	}
	logoTime += 0.01;
}

void LogoState::handle_events()
{
	return;
}


void LogoState::draw()
{
	Rectangle(mDC, -1, -1, screen.right, screen.bottom);
	logo.Draw(mDC, (screen.right-logo.GetWidth())/2, (screen.bottom - logo.GetHeight()) / 2,
		logo.GetWidth(), logo.GetHeight());
}
