#pragma once
#include"Animation.h"
#include"Vector2D.h"

const int BulletDamage[]{ 0,10,7,4 };

class Bullet
{
protected:
	Animation animation;
	float frame;
	Vector2D<float> pos;
	Vector2D<float> dir;
	int damage;
	int type;
public:
	int GetDamage() { return damage; }
	Bullet(int type, Vector2D<float> pos, Vector2D<float> dir) :type(type), pos(pos), dir(dir),
		damage(BulletDamage[type]), frame(0) { SetImage(type); }
	void SetImage(int type);
	void draw_bullet(HDC mDC);
	void update();
};