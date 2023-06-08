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
	if (logoTime > 1.5) {
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
	logo.Draw(mDC, 0, 0, screen.right, screen.bottom);
}
