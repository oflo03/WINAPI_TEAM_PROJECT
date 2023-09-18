#pragma once
#include "game_framework.h"
#include "Boss.h"
#include "Player.h"

class BossDieScene :
    public GameState
{
private:
	Boss* boss;
	Player* player;
	int time;
	int dir;
	RECT r1;
	RECT r2;
	HFONT rom;
public:
	BossDieScene();
	~BossDieScene();
	virtual void update();
	virtual void handle_events();
	virtual void draw();
};

