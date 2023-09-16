#include "EnemyManager.h"
#include"PistolMan.h"
#include"RifleMan.h"
#include"ShotgunMan.h"
#include"Bat.h"
#include"Bombshe.h"

Animation spawnAnim;

EnemyManager::EnemyManager()
{
	PistolMan::init();
	RifleMan::init();
	ShotgunMan::init();
	Bat::init();
	Bombshe::init();
	spawnAnim.resource.Load(L"resources/Enemy_Spawn.png");
	spawnAnim.frame = 17;
	spawnAnim.size = RECT(0, 0, 40, 40);
	spawnAnim.velocity = 0.5;
}

EnemyManager::~EnemyManager()
{
	enemy.clear();
	PistolMan::release();
	RifleMan::release();
	ShotgunMan::release();
	Bat::release();
	Bombshe::release();
	spawnAnim.resource.Destroy();
	spawnAnim.resource.Destroy();
	PistolMan::release();
	RifleMan::release();
	ShotgunMan::release();
	Bat::release();
	Bombshe::release();
}

EnemyManager* EnemyManager::getInstance()
{
	if (instance == nullptr)
		instance = new EnemyManager();
	return instance;
}

void EnemyManager::Clear()
{
	enemy.clear();
}

void EnemyManager::SetEnemy(int stage)
{
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
		spawn(SHOTGUNMAN, 760, 980);
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
		spawn(SHOTGUNMAN, 100, 970);
		spawn(SHOTGUNMAN, 1800, 970);
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


void EnemyManager::spawn(int type, float x, float y)
{
	switch (type)
	{
	case PISTOLMAN:
		enemy.emplace_back(new PistolMan(x, y, Player::getInstance()));
		break;
	case RIFLEMAN:
		enemy.emplace_back(new RifleMan(x, y, Player::getInstance()));
		break;
	case SHOTGUNMAN:
		enemy.emplace_back(new ShotgunMan(x, y, Player::getInstance()));
		break;
	case BAT:
		enemy.emplace_back(new Bat(x, y, Player::getInstance()));
		break;
	case BOMBSHE:
		enemy.emplace_back(new Bombshe(x, y, Player::getInstance()));
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

bool EnemyManager::isclear()
{
	return enemy.empty();
}

void EnemyManager::handle_event()
{
	for (int i = 0; i < enemy.size();i++) {
		if (!(enemy[i]->isDead()))
			enemy[i]->handle_event();
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