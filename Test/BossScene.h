#pragma once
#include "game_framework.h"
class BossScene :
    public GameState
{
protected:
	CImage scene;
	float time;
	RECT rect;
public:
	BossScene();
	~BossScene();
	virtual void update();
	virtual void handle_events();
	virtual void draw();
};

