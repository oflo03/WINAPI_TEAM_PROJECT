#pragma once
#include "Player.h"

class Player;

class Marin :
    public Player
{
private:
	Animation animation[6][6];
public:
	Marin(float x, float y);
	virtual ~Marin();
	virtual void draw_character(HDC mDC);
	virtual void handle_event();
	virtual void update();
	virtual void SetDirection();
	virtual void handle_collision(int otherLayer, int damage);
};