#pragma once
#include "game_framework.h"
#include"EnemyManager.h"
#include"EffectManager.h"
#include"Player.h"
#include"DropItem.h"
#include"Boss.h"
#include"Portal.h"
#include"MapManager.h"
#include"UI.h"
#include"LevelManager.h"
#include"SelectState.h"
#include"GameOverState.h"
#include"EndingState.h"
#include"OptionState.h"
#include"SoundManager.h"
#include"BossDieScene.h"
#include<random>


class PlayState :
    public GameState
{
public:
	PlayState();
	~PlayState();
	virtual void update();
	virtual void handle_events();
	virtual void draw();
private:
	Player* player;
	UI* ui;
	EnemyManager* enemyManager;
	EffectManager* effectManager;
	LevelManager* levelManager;
	SoundManager* soundManager;
	MapManager* mapManager;
	Portal* portal;
	Boss* boss;
};
