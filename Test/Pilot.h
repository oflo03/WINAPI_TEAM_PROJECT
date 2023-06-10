#pragma once
#include "Player.h"

class Player;

class Pilot :
	public Player
{
private:
	static Animation animation[5][6];
public:
	Pilot(float x, float y);
	virtual ~Pilot();
	static void init();
	virtual void draw_character(HDC mDC);
	virtual void handle_event();
	virtual void update();
	virtual void SetDirection();
	virtual void handle_collision(int otherLayer, int damage);
};