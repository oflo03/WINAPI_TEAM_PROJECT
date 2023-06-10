#include"PlayState.h"
#include"EnemyManager.h"
#include"EffectManager.h"
#include"Player.h"
#include"DropItem.h"
#include"Boss.h"
#include"UI.h"

extern HDC mDC;
std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_int_distribution<int> uid(1, 10000);
std::uniform_int_distribution<int> rad(-180, 180);
std::uniform_int_distribution<int> ranTime(20, 70);
std::uniform_int_distribution<int> ran(0, 1);
std::uniform_int_distribution<int> randrop(0, 1);
std::uniform_int_distribution<int> ranP(0, 2);

void ColliderUpdate();
void LoadTileMap(int num);
void PrintMap(HDC mDC);

std::vector<Collider*> COLL;
std::vector<Bullet*> Bullets;
std::vector<DropItem*> drops;
extern Vector2D<float> monitorSize;
extern Vector2D<float> camSize;
Vector2D<float> camPos;

bool lookRange;
bool beatable;

PlayState::PlayState() : GameState()	// 모든 스테이트 시작 전에 콜라이더 벡터 초기화 하는거 넣어줘요 - 병욱
{
	Player::init();
	EnemyManager::getInstance()->init(8);
	EffectManager::init();
	Bullet::init();
	DropItem::init();
	LoadTileMap(3);
	UI::init();
	beatable = true;
	//PlaySound(L"BGM_PlayState.wav", NULL, SND_ASYNC | SND_LOOP);
}

PlayState::~PlayState()
{
	Player::Destroy();
	EnemyManager::destroy();
}

void PlayState::update()
{
	for (auto& d : drops)
		d->update();
	Player::getInstance(1)->update();
	EnemyManager::getInstance()->update();
	Boss::getInstance()->update();
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
	else if (GetAsyncKeyState('Z') & 1) {
		beatable = !beatable;
	}
	EnemyManager::getInstance()->handle_event();
	Player::getInstance(1)->handle_event();
	Boss::getInstance()->handle_event();
}



void PlayState::draw()
{
	HDC mapDC = CreateCompatibleDC(mDC);
	HBITMAP mapbitmap = CreateCompatibleBitmap(mDC, 1920, 1080);
	SelectObject(mapDC, mapbitmap);
	PrintMap(mapDC);
	for (auto& d : drops)
		d->Draw(mapDC);
	EnemyManager::getInstance()->draw(mapDC);
	Player::getInstance(1)->draw_character(mapDC);
	Boss::getInstance()->draw(mapDC);
	for (auto& B : Bullets)
		B->draw_bullet(mapDC);
	if (lookRange)
		for (auto& c : COLL)
			c->draw_range(mapDC);
	EffectManager::getInstance()->Draw(mapDC);
	StretchBlt(mDC, 0, 0, screen.right, screen.bottom,
		mapDC, camPos.x - camSize.x, camPos.y - camSize.y, camSize.x * 2, camSize.y * 2, SRCCOPY);
	DeleteObject(mapbitmap);
	DeleteDC(mapDC);
	UI::draw(mDC);
}