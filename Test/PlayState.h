#pragma once
#include "game_framework.h"
#include"Marin.h"
#include<random>


class PlayState :
    public GameState
{
private:
	Player* player;
public:
	PlayState();
	~PlayState();
	virtual void update();
	virtual void handle_events();
	virtual void draw();
};

