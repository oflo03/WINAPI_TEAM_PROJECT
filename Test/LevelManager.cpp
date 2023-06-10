#include "LevelManager.h"
#include"PlayState.h"
#include"EnemyManager.h"
#include"EffectManager.h"
#include"Player.h"
#include"DropItem.h"
#include"Boss.h"
#include"UI.h"
#include"Portal.h"
#include"MapManager.h"

extern bool enemyclear;

Vector2D<float> portalpoint[4]{
	Vector2D<float>(1633,256),
	Vector2D<float>(960,900),
	Vector2D<float>(960,540),
	Vector2D<float>(960,540)
};

void LevelManager::init()
{
	MapManager::getInstance()->LoadTileMap(1);
	EnemyManager::getInstance()->SetEnemy(1);
}

void LevelManager::destroy()
{
	if (instance != nullptr)
		delete instance;
}

LevelManager* LevelManager::getInstance()
{
	if (instance == nullptr)
		instance = new LevelManager();
	return instance;
}

void LevelManager::update()
{
	if (EnemyManager::getInstance()->isclear()) {
		if (phase == 3) {
			Portal::getInstance()->SetPos(portalpoint[stage - 1]);
			enemyclear = true;
		}
		else if (stage != 4)
		{
			++phase;
			EnemyManager::getInstance()->SetEnemy((stage - 1) * 3 + phase);
		}
	}
	else enemyclear = false;
}

void LevelManager::loadNextStage()
{
	++stage;
	phase = 1;
	Collider::Clear();
	DropItem::Clear();
	COLL.emplace_back(Player::getInstance()->col);
	MapManager::getInstance()->LoadTileMap(stage);
	EnemyManager::getInstance()->SetEnemy((stage - 1) * 3 + phase);
	enemyclear = false;
	Player::getInstance()->SetPos(spawnpoint[stage - 1]);
}

LevelManager* LevelManager::instance = nullptr;