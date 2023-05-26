#pragma once
#include "Player.h"

class Marin :
    public Player
{
public:
	Marin(float x, float y);
	Marin();
	virtual ~Marin();
	virtual void draw_character(HDC mDC);
	virtual void handle_event();
	virtual void update();
	virtual void SetImage(int state);
	virtual void change_frame();
};

