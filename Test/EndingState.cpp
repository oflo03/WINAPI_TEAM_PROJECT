#include "EndingState.h"
#include "SelectState.h"

extern HDC mDC;
extern RECT screen;
bool IsAnyKeyPressed();

EndingState::EndingState()
{
	back.Load(L"Ending.png");
}

EndingState::~EndingState()
{
	back.Destroy();
}

void EndingState::update()
{

}
void EndingState::handle_events()
{

	if (GetAsyncKeyState(VK_ESCAPE)) {
		PostQuitMessage(0);
		return;
	}
	else if (IsAnyKeyPressed()) {
		change_state(new SelectState);
	}
}
void EndingState::draw()
{
	back.Draw(mDC, 0, 0, screen.right, screen.bottom);
}