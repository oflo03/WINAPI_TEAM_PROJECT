#pragma once
#include"Master.h"
#include"Player.h"

extern RECT screen;

class Boss : public Master
{
private:
	CImage shadow;
	float frame;
	float angle;
	Vector2D<float> pos;
};

