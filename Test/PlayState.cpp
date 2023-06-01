#include "PlayState.h"

extern HDC mDC;

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_int_distribution<int> uid(1, 10000);

PlayState::PlayState() : GameState(),player(new Marin)
{

}

PlayState::~PlayState()
{
	delete player;
}

void PlayState::update()
{
	player->update();
}

void PlayState::handle_events()
{
	if (GetAsyncKeyState(VK_ESCAPE)) {
		PostQuitMessage(0);
		return;
	}
	player->handle_event();
}



void PlayState::draw()
{
	player->draw_character(mDC);
}
