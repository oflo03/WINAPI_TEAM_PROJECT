#pragma once
#include "game_framework.h"
#include"Marin.h"
#include"PistolMan.h"
#include<random>


class PlayState :
    public GameState
{
private:
	Player* player;
	std::vector<std::unique_ptr<Enemy>> enemy;
public:
	PlayState();
	~PlayState();
	virtual void update();
	virtual void handle_events();
	virtual void draw();
};

