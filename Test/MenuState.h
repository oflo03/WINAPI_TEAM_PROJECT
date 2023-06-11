#pragma once
#include "game_framework.h"
#include"SoundManager.h"

class MenuState :
    public GameState
{
private:
	CImage title;
	SoundManager* sound;
public:
	MenuState();
	~MenuState();
	virtual void update();
	virtual void handle_events();
	virtual void draw();
};

