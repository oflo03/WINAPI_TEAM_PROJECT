#pragma once
#include <atlImage.h>

struct Animation
{
	CImage resource;
	RECT size;
	int frame;
	float velocity;
};

enum STATE
{
	STATE_IDLE, STATE_RUN,STATE_DAMAGED,STATE_DEAD, STATE_ROLL
};

enum DIRECTION
{
	FRONT, FRONT_RIGHT, FRONT_LEFT, BACK, BACK_RIGHT, BACK_LEFT
};