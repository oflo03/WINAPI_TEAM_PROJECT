#pragma once
#include"Collider.h"

struct Master
{
	Collider* col;
	virtual void handle_collision(int otherLayer) = 0;
};

struct CollisionMessage
{
	Master* collided;
	int otherLayer;
};