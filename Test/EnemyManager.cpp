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
	switch (stage)
	{
	case 1:
		enemy.emplace_back(new PistolMan(300, 400, Player::getInstance(1)));
		enemy.emplace_back(new RifleMan(350, 400, Player::getInstance(1)));
		enemy.emplace_back(new ShotgunMan(350, 500, Player::getInstance(1)));
		enemy.emplace_back(new Bat(400, 500, Player::getInstance(1)));
		enemy.emplace_back(new Bombshe(400, 500, Player::getInstance(1)));
		break;
	case 2:
		break;
	case 3:
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