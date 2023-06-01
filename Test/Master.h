#pragma once
#include"Collider.h"

class Master
{
	Collider col;
	virtual void handle_collision(int damage) = 0;
};