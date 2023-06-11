#include "MenuState.h"
#include "SelectState.h"
#include"SoundManager.h"

extern HDC mDC;
extern RECT screen;

MenuState::MenuState()
{
	title.Load(L"main_title.png");
	SoundManager::getInstance()->play(TitleState);
}
MenuState::~MenuState()
{
	title.Destroy();
}

void MenuState::update()
{

}

void MenuState::handle_events()
{
	if (GetAsyncKeyState(VK_ESCAPE)&1) {
		PostQuitMessage(0);
		return;
	}
	else if (GetAsyncKeyState('E') & 1)
	{
		change_state(new SelectState);
	}
}

void MenuState::draw()
{
	title.Draw(mDC, 0, 0, screen.right, screen.bottom, 0, 0, 1920, 1080);
}
