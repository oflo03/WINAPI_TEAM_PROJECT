#include "PlayState.h"

extern HDC mDC;

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_int_distribution<int> uid(1, 10000);

void ColliderUpdate();

std::queue<Vector2D<Master*>> collisionMsg;
std::vector<Collider*> COLL;

CImage map;
bool lookRange;

PlayState::PlayState() : GameState(), player(new Marin)
{
	map.Load(L"testmap.png");
}

PlayState::~PlayState()
{
	delete player;
}

void PlayState::update()
{
	player->update();
	ColliderUpdate();
}

void PlayState::handle_events()
{
	if (GetAsyncKeyState(VK_ESCAPE)) {
		PostQuitMessage(0);
		return;
	}
	else if (GetAsyncKeyState('X') & 1) {
		lookRange = !lookRange;
	}
	player->handle_event();
}



void PlayState::draw()
{
	map.Draw(mDC, 0, 28, 1024, 1024);
	player->draw_character(mDC);
	if (lookRange)
		for (auto& C : COLL)
			C->draw_range(mDC);
}
