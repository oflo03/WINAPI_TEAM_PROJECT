#pragma once
#include "Player.h"

class Player;

class Knight :
	public Player
{
private:
	static Animation animation[5][6];
public:
	Knight(float x, float y);
	virtual ~Knight();
	static void init();
	virtual void draw_character(HDC mDC);
	virtual void handle_event();
	virtual void update();
	virtual void SetDirection();
	virtual void handle_collision(int otherLayer, int damage);
};