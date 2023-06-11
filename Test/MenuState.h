#pragma once
#include "game_framework.h"

class MenuState :
    public GameState
{
private:
	CImage title;
public:
	MenuState();
	~MenuState();
	virtual void update();
	virtual void handle_events();
	virtual void draw();
};

