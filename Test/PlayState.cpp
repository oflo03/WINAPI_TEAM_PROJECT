#include "PlayState.h"

extern HDC mDC;

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_int_distribution<int> uid(1, 10000);

void ColliderUpdate();
void LoadTileMap();
void PrintMap(HDC mDC);

std::vector<std::unique_ptr<Collider>> COLL;
std::vector<Bullet*> Bullets;

bool lookRange;

PlayState::PlayState() : GameState(), player(new Marin)
{
	enemy.emplace_back(new PistolMan(300, 400, player));
	LoadTileMap();

}

PlayState::~PlayState()
{
	delete player;
	enemy.clear();
}

void PlayState::update()
{
	player->col->layer = 1;
	player->update();
	for (auto& E : enemy)
		E->update();
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
	for (auto& E : enemy)
		E->handle_event();
}



void PlayState::draw()
{
	PrintMap(mDC);
	for (auto& B : Bullets)
		B->draw_bullet(mDC);
	player->draw_character(mDC);
	for (auto& E : enemy)
		E->draw_character(mDC);
	if (lookRange)
		for (auto& c : COLL)
			c->draw_range(mDC);
}
