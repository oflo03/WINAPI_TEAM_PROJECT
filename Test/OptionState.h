#pragma once
#include "game_framework.h"
class OptionState :
    public GameState
{
public:
	OptionState();
	~OptionState();
	virtual void update();
	virtual void handle_events();
	virtual void draw();
private:
	CImage background;
	CImage black;
	CImage control;
	HFONT font;
	TCHAR string1[10];
	TCHAR string2[10];
	TCHAR string3[10];
	RECT rect[3];
	bool isOn[3];
	bool controlOn;
};

