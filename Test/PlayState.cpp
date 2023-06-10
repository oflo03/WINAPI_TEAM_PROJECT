#include"PlayState.h"
#include"EnemyManager.h"
#include"EffectManager.h"
#include"Player.h"
#include"DropItem.h"
#include"Boss.h"
#include"UI.h"
#include"Portal.h"
#include"MapManager.h"
#include"LevelManager.h"

extern HDC mDC;
std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_int_distribution<int> uid(1, 10000);
std::uniform_int_distribution<int> rad(-180, 180);
std::uniform_int_distribution<int> ranTime(20, 70);
std::uniform_int_distribution<int> ran(0, 1);
std::uniform_int_distribution<int> randrop(0, 1);

void ColliderUpdate();

std::vector<Collider*> COLL;
std::vector<Bullet*> Bullets;
std::vector<DropItem*> drops;
extern Vector2D<float> monitorSize;
extern Vector2D<float> camSize;
Vector2D<float> camPos;

bool lookRange;
bool beatable = true;
bool enemyclear;

PlayState::PlayState() : GameState()	// 모든 스테이트 시작 전에 콜라이더 벡터 초기화 하는거 넣어줘요 - 병욱
{
	LevelManager::init();
	Player::init();
	EnemyManager::init();
	EffectManager::init();
	Bullet::init();
	DropItem::init();
	UI::init();
	//PlaySound(L"BGM_PlayState.wav", NULL, SND_ASYNC | SND_LOOP);
}

PlayState::~PlayState()
{
	LevelManager::destroy();
	Player::Destroy();
	EnemyManager::destroy();
}

void PlayState::update()
{
	LevelManager::getInstance()->update();
	for (auto& d : drops)
		d->update();
	Player::getInstance()->update();
	EnemyManager::getInstance()->update();
	if (LevelManager::getInstance()->GetStage() == 4)
		Boss::getInstance()->update();
	if (enemyclear)
		Portal::getInstance()->update();
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
	if (enemyclear)
		Portal::getInstance()->handle_event();
	EnemyManager::getInstance()->handle_event();
	Player::getInstance()->handle_event();
	if (LevelManager::getInstance()->GetStage() == 4)
		Boss::getInstance()->handle_event();
}



void PlayState::draw()
{
	HDC mapDC = CreateCompatibleDC(mDC);
	HBITMAP mapbitmap = CreateCompatibleBitmap(mDC, 1920, 1080);
	SelectObject(mapDC, mapbitmap);
	MapManager::getInstance()->PrintMap(mapDC);
	for (auto& d : drops)
		d->Draw(mapDC);
	EnemyManager::getInstance()->draw(mapDC);
	if (enemyclear)
		if (Player::getInstance()->GetPos().y - Portal::getInstance()->GetPos().y > 0) {
			Portal::getInstance()->Draw(mapDC);
			Player::getInstance()->draw_character(mapDC);
		}
		else {
			Player::getInstance()->draw_character(mapDC);
			Portal::getInstance()->Draw(mapDC);
		}
	else
		Player::getInstance()->draw_character(mapDC);
	if (LevelManager::getInstance()->GetStage() == 4)
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