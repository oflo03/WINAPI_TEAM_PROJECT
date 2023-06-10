#pragma once
#include "game_framework.h"
class SelectState :
    public GameState
{
private:
	CImage background;
	double logoTime;
public:
	SelectState();
	~SelectState();
	virtual void update();
	virtual void handle_events();
	virtual void draw();
};

