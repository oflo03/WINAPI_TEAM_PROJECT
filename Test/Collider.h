#pragma once
#include<Windows.h>
#include<vector>
#include<queue>
#include"Vector2D.h"

enum shapetype
{
	point, rect, circle
};

std::queue<Vector2D<int>> collisionMsg;

class Collider
{
protected:
	Vector2D<float> pos;
	int size;
	int shape;
	int layer;

public:
	void collision();
};

std::vector<Collider*> COLL;

void rigidUpdate()
{
	for (auto& c : COLL)
		c->collision();

}