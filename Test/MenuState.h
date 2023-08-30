#pragma once
#include "game_framework.h"

class MenuState :
    public GameState
{
private:
	CImage title;
	HFONT font;
	TCHAR string1[10];
	TCHAR string2[10];
	TCHAR string3[10];
	RECT rect[3];
	bool isOn[3];
public:
	MenuState();
	~MenuState();
	virtual void update();
	virtual void handle_events();
	virtual void draw();
};

