#pragma once
#include "game_framework.h"
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
};
