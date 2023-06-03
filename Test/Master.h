#pragma once
#include"Collider.h"

struct Master
{
	Collider* col;
	virtual void handle_collision(Master* other) = 0;
};