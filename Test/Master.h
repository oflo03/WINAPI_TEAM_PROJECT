#pragma once
#include"Collider.h"

struct Master
{
	Collider* col;
	virtual void handle_collision(int otherLayer, int damage) = 0;
	bool isDead() { return (col == nullptr); }
};

struct CollisionMessage
{
	Master* collided;
	int otherLayer;
	int damage;
};