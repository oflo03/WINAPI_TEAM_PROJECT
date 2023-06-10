#include "EnemyManager.h"
#include"PistolMan.h"
#include"RifleMan.h"
#include"ShotgunMan.h"
#include"Bat.h"
#include"Bombshe.h"

Animation spawnAnim;

EnemyManager::~EnemyManager()
{
	enemy.clear();
	PistolMan::release();
	RifleMan::release();
	ShotgunMan::release();
	Bat::release();
	Bombshe::release();
	spawnAnim.resource.Destroy();
}

EnemyManager* EnemyManager::getInstance()
{
	if (instance == nullptr)
		instance = new EnemyManager();
	return instance;
}

void EnemyManager::init(int stage)
{
	PistolMan::init();
	RifleMan::init();
	ShotgunMan::init();
	Bat::init();
	Bombshe::init();
	Player* player = Player::getInstance(selectedPlayer);
	spawnAnim.resource.Load(L"Enemy_Spawn.png");
	spawnAnim.frame = 17;
	spawnAnim.size = RECT(0, 0, 40, 40);
	spawnAnim.velocity = 0.5;
	switch (stage)
	{
	case 1:
		spawn(PISTOLMAN, 300, 400);
		spawn(PISTOLMAN, 1000, 400);
		spawn(PISTOLMAN, 1800, 400);
		break;
	case 2:
		spawn(PISTOLMAN, 300, 400);
		spawn(PISTOLMAN, 1000, 400);
		spawn(PISTOLMAN, 1800, 400);
		spawn(PISTOLMAN, 300, 900);
		spawn(PISTOLMAN, 1000, 900);
		spawn(PISTOLMAN, 1800, 900);
		break;
	case 3:
		spawn(RIFLEMAN, 300, 400);
		spawn(PISTOLMAN, 1000, 400);
		spawn(PISTOLMAN, 1800, 400);
		spawn(PISTOLMAN, 300, 900);
		spawn(PISTOLMAN, 1000, 900);
		spawn(RIFLEMAN, 1800, 900);
		break;
	case 4:
		spawn(PISTOLMAN, 600, 200);
		spawn(PISTOLMAN, 1500, 200);
		spawn(RIFLEMAN, 300, 600);
		spawn(RIFLEMAN, 1800, 600);
		spawn(SHOTGUNMAN, 960, 1000);
		break;
	case 5:
		spawn(BAT, 300, 200);
		spawn(BAT, 1600, 200);
		spawn(BAT, 600, 600);
		spawn(BAT, 1500, 600);
		break;
	case 6:
		spawn(SHOTGUNMAN, 600, 200);
		spawn(SHOTGUNMAN, 1300, 200);
		spawn(BAT, 300, 600);
		spawn(BAT, 1800, 600);
		spawn(SHOTGUNMAN, 100, 800);
		spawn(SHOTGUNMAN, 1850, 800);
		spawn(BAT, 300, 1000);
		spawn(BAT, 1800, 1000);
		break;
	case 7:
		spawn(BOMBSHE, 400, 600);
		spawn(BOMBSHE, 1500, 600);
		spawn(PISTOLMAN, 800, 300);
		spawn(PISTOLMAN, 1000, 300);
		spawn(RIFLEMAN, 800, 800);
		spawn(RIFLEMAN, 1000, 800);
		break;
	case 8:
		spawn(SHOTGUNMAN, 800, 300);
		spawn(SHOTGUNMAN, 1000, 300);
		spawn(SHOTGUNMAN, 800, 800);
		spawn(SHOTGUNMAN, 1000, 800);
		spawn(SHOTGUNMAN, 300, 200);
		spawn(SHOTGUNMAN, 1600, 200);
		spawn(SHOTGUNMAN, 300, 600);
		spawn(SHOTGUNMAN, 1800, 600);
		break;
	case 9:
		spawn(PISTOLMAN, 800, 300);
		spawn(PISTOLMAN, 1000, 300);
		spawn(RIFLEMAN, 800, 800);
		spawn(RIFLEMAN, 1000, 800);
		spawn(SHOTGUNMAN, 300, 200);
		spawn(SHOTGUNMAN, 1600, 200);
		spawn(BAT, 300, 600);
		spawn(BAT, 1800, 600);
		break;
	default:
		break;
	}
}

void EnemyManager::destroy()
{
	if (instance != nullptr)
		delete instance;
}

void EnemyManager::spawn(int type, float x, float y)
{
	switch (type)
	{
	case PISTOLMAN:
		enemy.emplace_back(new PistolMan(x, y, Player::getInstance(selectedPlayer)));
		break;
	case RIFLEMAN:
		enemy.emplace_back(new RifleMan(x, y, Player::getInstance(selectedPlayer)));
		break;
	case SHOTGUNMAN:
		enemy.emplace_back(new ShotgunMan(x, y, Player::getInstance(selectedPlayer)));
		break;
	case BAT:
		enemy.emplace_back(new Bat(x, y, Player::getInstance(selectedPlayer)));
		break;
	case BOMBSHE:
		enemy.emplace_back(new Bombshe(x, y, Player::getInstance(selectedPlayer)));
		break;
	default:
		break;
	}
}

void EnemyManager::delete_enemy(Enemy* e)
{
	for (auto i = enemy.begin(); i != enemy.end(); ++i)
		if (enemy[i - enemy.begin()] == e)
		{
			enemy.erase(i);
			break;
		}
}

void EnemyManager::handle_event()
{
	for (auto& E : enemy) {
		if (!E->isDead())
			E->handle_event();
	}
}

void EnemyManager::update()
{
	for (auto& E : enemy)
		E->update();
	std::sort(enemy.begin(), enemy.end(), [](const Enemy* e1, const Enemy* e2) {return e1->GetPos().y < e2->GetPos().y; });
}

void EnemyManager::draw(HDC mDC)
{
	for (auto& E : enemy)
		E->draw_character(mDC);
}

EnemyManager* EnemyManager::instance = nullptr;