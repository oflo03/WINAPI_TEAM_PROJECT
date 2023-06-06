#include "PlayState.h"

extern HDC mDC;

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_int_distribution<int> uid(1, 10000);

void ColliderUpdate();
void LoadTileMap(int num);
void PrintMap(HDC mDC);

std::vector<Collider*> COLL;
std::vector<Bullet*> Bullets;

bool lookRange;

PlayState::PlayState() : GameState(), player(new Marin)	// 모든 스테이트 시작 전에 콜라이더 벡터 초기화 하는거 넣어줘요 - 병욱
{
	enemy.emplace_back(new PistolMan(300, 400, player));
	LoadTileMap(2);
}

PlayState::~PlayState()
{
	delete player;
	enemy.clear();
}

void PlayState::update()
{
	for (auto& E : enemy)
		E->update();
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
	for (auto& E : enemy)
		E->handle_event();
	player->handle_event();
}



void PlayState::draw()
{
	PrintMap(mDC);
	for (auto& B : Bullets)
		B->draw_bullet(mDC);
	for (auto& E : enemy)
		E->draw_character(mDC);
	player->draw_character(mDC);
	if (lookRange)
		for (auto& c : COLL)
			c->draw_range(mDC);
}
