#pragma once
#include <atlImage.h>

struct Animation
{
	CImage resource;
	RECT size;
	int frame;
};

enum STATE
{
	STATE_IDLE, STATE_RUN, STATE_ROLL,STATE_DAMAGED
};

enum DIRECTION
{
	FRONT, FRONT_RIGHT, FRONT_LEFT, BACK, BACK_RIGHT, BACK_LEFT
};