#include "PlayState.h"

extern HDC mDC;

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_int_distribution<int> uid(1, 10000);

void ColliderUpdate();
void LoadTileMap();
void PrintMap(HDC mDC);

std::vector<Collider*> COLL;
std::vector<Bullet*> Bullets;

CImage map;
bool lookRange;

PlayState::PlayState() : GameState(), player(new Marin)
{
	map.Load(L"testmap.png");
	LoadTileMap();
}

PlayState::~PlayState()
{
	delete player;
}

void PlayState::update()
{
	player->update();
	for (auto& B : Bullets)
		B->update();
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
	PrintMap(mDC);
	for (auto& B : Bullets)
		B->draw_bullet(mDC);
	player->draw_character(mDC);
	if (lookRange)
		for (auto& C : COLL)
			C->draw_range(mDC);
}
