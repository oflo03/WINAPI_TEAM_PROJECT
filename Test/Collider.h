#pragma once
#include<Windows.h>
#include<vector>
#include<queue>
#include<unordered_set>
#include"Vector2D.h"
#include <memory>

enum shapetype
{
	point, rect, circle
};

enum layertype
{
	wall, player, rolled_player, enemy, playerBullet, enemyBullet, playerMelee, damaged_player,dropitem
};

class Master;

struct Collider
{
	Vector2D<float> pos;
	Vector2D<float> size;
	int shape;
	int layer;
	int damage;
	Master* owner;
	Collider() : size(0, 0), shape(point){ }
	Collider(float rad) : size(rad, rad), shape(circle){ }
	Collider(Vector2D<float> size) : size(size), shape(rect){ }
	void detection();
	void draw_range(HDC mDC);
};

bool isWallCollision(Vector2D<float> pos, Vector2D<float> size);
extern std::vector<Collider*> COLL;
extern std::unordered_set<Master*> deleteSet;