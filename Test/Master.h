#pragma once
#include"Collider.h"

struct Master
{
	Collider* col;
	virtual void handle_collision(int damage) = 0;
};