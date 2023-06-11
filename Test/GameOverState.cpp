#include "GameOverState.h"
#include "SelectState.h"

extern HDC mDC;
extern RECT screen;
bool IsAnyKeyPressed();

GameOverState::GameOverState()
{
	back.Load(L"GameOver.png");
}

GameOverState::~GameOverState()
{
	back.Destroy();
}

void GameOverState::update()
{

}
void GameOverState::handle_events()
{

	if (GetAsyncKeyState(VK_ESCAPE)) {
		change_state(new SelectState);
	}
}
void GameOverState::draw()
{
	back.Draw(mDC, 0, 0, screen.right, screen.bottom);
}