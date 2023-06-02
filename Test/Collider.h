#pragma once
#include<Windows.h>
#include<vector>
#include<queue>
#include"Vector2D.h"


enum shapetype
{
	point, rect, circle
};

enum layertype
{
	wall, player, enemy, playerBullet, enemyBullet
};

class Master;

struct Collider
{
	Vector2D<float> pos;
	Vector2D<float> size;
	int shape;
	int layer;
	Master* owner;
	Collider() : size(0, 0), shape(point) { }
	Collider(float rad) : size(rad, rad), shape(circle) { }
	Collider(Vector2D<float> size) : size(size), shape(rect) { }
	void detection();
	void draw_range(HDC mDC);
};

extern std::queue<Vector2D<Master*>> collisionMsg;
extern std::vector<Collider*> COLL;
