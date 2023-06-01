#pragma once
#include "game_framework.h"
class LogoState :
    public GameState
{
private:
	CImage logo;
	double logoTime;
public:
	LogoState();
	~LogoState();
	virtual void update();
	virtual void handle_events();
	virtual void draw();
};