#include"PlayState.h"
#include"EnemyManager.h"
#include"EffectManager.h"
#include"Player.h"

extern HDC mDC;
std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_int_distribution<int> uid(1, 10000);
std::uniform_int_distribution<int> rad(-180, 180);
std::uniform_int_distribution<int> ranTime(20, 100);
std::uniform_int_distribution<int> ran(0, 1);

void ColliderUpdate();
void LoadTileMap(int num);
void PrintMap(HDC mDC);

std::vector<Collider*> COLL;
std::vector<Bullet*> Bullets;

bool lookRange;

PlayState::PlayState() : GameState()	// 모든 스테이트 시작 전에 콜라이더 벡터 초기화 하는거 넣어줘요 - 병욱
{
	EnemyManager::getInstance()->init(1);
	LoadTileMap(2);
	PlaySound(L"BGM_PlayState.wav", NULL, SND_ASYNC | SND_LOOP);
}

PlayState::~PlayState()
{
	Player::Destroy();
	EnemyManager::destroy();
}

void PlayState::update()
{

	EnemyManager::getInstance()->update();
	Player::getInstance(1)->update();
	for (auto& B : Bullets)
		B->update();
	EffectManager::getInstance()->update();
	ColliderUpdate();
	EffectManager::getInstance()->delete_effect();
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
	EnemyManager::getInstance()->handle_event();
	Player::getInstance(1)->handle_event();
}



void PlayState::draw()
{
	PrintMap(mDC);
	EnemyManager::getInstance()->draw(mDC);
	Player::getInstance(1)->draw_character(mDC);
	for (auto& B : Bullets)
		B->draw_bullet(mDC);
	if (lookRange)
		for (auto& c : COLL)
			c->draw_range(mDC);
	EffectManager::getInstance()->Draw(mDC);
}
