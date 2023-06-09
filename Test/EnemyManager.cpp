#include "EnemyManager.h"
#include"PistolMan.h"
#include"RifleMan.h"
#include"ShotgunMan.h"
#include"Bat.h"
#include"Bombshe.h"
EnemyManager::~EnemyManager()
{
	enemy.clear();
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

void EnemyManager::init(int stage)
{
	PistolMan::init();
	RifleMan::init();
	ShotgunMan::init();
	Bat::init();
	Bombshe::init();
	Player* player = Player::getInstance(1);
	switch (stage)
	{
	case 1:
		enemy.emplace_back(new PistolMan(300, 400, Player::getInstance(1)));
		enemy.emplace_back(new PistolMan(1000, 400, Player::getInstance(1)));
		enemy.emplace_back(new PistolMan(1800, 400, Player::getInstance(1)));
		break;
	case 2:
		enemy.emplace_back(new PistolMan(300, 400, Player::getInstance(1)));
		enemy.emplace_back(new PistolMan(1000, 400, Player::getInstance(1)));
		enemy.emplace_back(new PistolMan(1800, 400, Player::getInstance(1)));
		enemy.emplace_back(new PistolMan(300, 900, Player::getInstance(1)));
		enemy.emplace_back(new PistolMan(1000, 900, Player::getInstance(1)));
		enemy.emplace_back(new PistolMan(1800, 900, Player::getInstance(1)));
		break;
	case 3:
		enemy.emplace_back(new RifleMan(300, 400, Player::getInstance(1)));
		enemy.emplace_back(new PistolMan(1000, 400, Player::getInstance(1)));
		enemy.emplace_back(new PistolMan(1800, 400, Player::getInstance(1)));
		enemy.emplace_back(new PistolMan(300, 900, Player::getInstance(1)));
		enemy.emplace_back(new PistolMan(1000, 900, Player::getInstance(1)));
		enemy.emplace_back(new RifleMan(1800, 900, Player::getInstance(1)));
		break;
	case 4:
		enemy.emplace_back(new PistolMan(600, 200, Player::getInstance(1)));
		enemy.emplace_back(new PistolMan(1500, 200, Player::getInstance(1)));
		enemy.emplace_back(new RifleMan(300, 600, Player::getInstance(1)));
		enemy.emplace_back(new RifleMan(1800, 600, Player::getInstance(1)));
		enemy.emplace_back(new ShotgunMan(960, 1000, Player::getInstance(1)));
		break;
	case 5:
		enemy.emplace_back(new Bat(300, 200, Player::getInstance(1)));
		enemy.emplace_back(new Bat(1600, 200, Player::getInstance(1)));
		enemy.emplace_back(new Bat(600, 600, Player::getInstance(1)));
		enemy.emplace_back(new Bat(1500, 600, Player::getInstance(1)));
		break;
	case 6:
		enemy.emplace_back(new ShotgunMan(600, 200, Player::getInstance(1)));
		enemy.emplace_back(new ShotgunMan(1300, 200, Player::getInstance(1)));
		enemy.emplace_back(new Bat(300, 600, Player::getInstance(1)));
		enemy.emplace_back(new Bat(1800, 600, Player::getInstance(1)));
		enemy.emplace_back(new ShotgunMan(100, 800, Player::getInstance(1)));
		enemy.emplace_back(new ShotgunMan(1850, 800, Player::getInstance(1)));
		enemy.emplace_back(new Bat(300, 1000, Player::getInstance(1)));
		enemy.emplace_back(new Bat(1800, 1000, Player::getInstance(1)));
		break;
	case 7:
		enemy.emplace_back(new Bombshe(400, 600, Player::getInstance(1)));
		enemy.emplace_back(new Bombshe(1500, 600, Player::getInstance(1)));
		enemy.emplace_back(new PistolMan(800, 300, Player::getInstance(1)));
		enemy.emplace_back(new PistolMan(1000, 300, Player::getInstance(1)));
		enemy.emplace_back(new RifleMan(800, 800, Player::getInstance(1)));
		enemy.emplace_back(new RifleMan(1000, 800, Player::getInstance(1)));
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	default:
		break;
	}
}

void EnemyManager::destroy()
{
	if(instance!=nullptr)
		delete instance;
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
		if(!E->isDead())
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