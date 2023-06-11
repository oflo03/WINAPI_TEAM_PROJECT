#pragma once
#include "game_framework.h"
class LogoState :
	public GameState
{
private:
	CImage tuk, logo, title;
	double logoTime;
	SoundManager* sound;
public:
	LogoState();
	~LogoState();
	virtual void update();
	virtual void handle_events();
	virtual void draw();
};