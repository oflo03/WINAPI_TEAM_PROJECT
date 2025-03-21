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
#include"BossScene.h"
#include"EndingState.h"

extern bool enemyclear;

Vector2D<float> portalpoint[4]{
	Vector2D<float>(1633,256),
	Vector2D<float>(960,900),
	Vector2D<float>(960,540),
	Vector2D<float>(960,540)
};

LevelManager::LevelManager() :stage(1), phase(1)
{
	MapManager::getInstance()->LoadTileMap(1);
	EnemyManager::getInstance()->SetEnemy(1);
}

LevelManager::~LevelManager()
{
}

LevelManager* LevelManager::getInstance()
{
	if (instance == nullptr)
		instance = new LevelManager();
	return instance;
}

void LevelManager::release()
{
	if (instance != nullptr)
		delete instance;
	instance = nullptr;
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
		else if (Boss::getInstance()->getHP() <= 0) {
			Portal::getInstance()->SetPos(portalpoint[stage - 1]);
			enemyclear = true;
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
	EnemyManager::getInstance()->Clear();
	Bullets.clear();
	Player::getInstance()->SetPos(spawnpoint[stage - 1]);
	if (stage == 4)
		push_state(new BossScene);
	else if (stage == 5) {
		change_state(new EndingState);
		return;
	}
	COLL.emplace_back(Player::getInstance()->col);
	MapManager::getInstance()->LoadTileMap(stage);
	EnemyManager::getInstance()->SetEnemy((stage - 1) * 3 + phase);
	enemyclear = false;
}

LevelManager* LevelManager::instance = nullptr;