#pragma once
#include<Windows.h>
#include<vector>
#include<queue>
#include"Vector2D.h"
#include <memory>

enum shapetype
{
	point, rect, circle
};

enum layertype
{
	wall, player, rolled_player, enemy, playerBullet, enemyBullet
};

class Master;

struct Collider
{
	Vector2D<float> pos;
	Vector2D<float> size;
	int shape;
	int layer;
	Master* owner;
	bool isInvalid;
	Collider() : size(0, 0), shape(point),isInvalid(false) { }
	Collider(float rad) : size(rad, rad), shape(circle), isInvalid(false) { }
	Collider(Vector2D<float> size) : size(size), shape(rect), isInvalid(false) { }
	void detection();
	void draw_range(HDC mDC);
};

extern std::vector<std::unique_ptr<Collider>> COLL;