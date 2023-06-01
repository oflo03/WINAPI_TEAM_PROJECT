#pragma once
#include<vector>
#include<queue>
#include"Vector2D.h"


enum shapetype
{
	point, rect, circle
};

class Master;

class Collider
{
protected:
	Vector2D<float> pos;
	int size;
	int shape;
	int layer;
	Master* owner;
public:
	void detection();
};

extern std::queue<Vector2D<int>> collisionMsg;
extern std::vector<Collider*> COLL;
