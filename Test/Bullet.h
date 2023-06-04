#pragma once
#include"Animation.h"
#include"Vector2D.h"
#include"Master.h"

const int BulletDamage[]{ 0,10,7,4 };

class Bullet
	:public Master
{
protected:
	Animation animation;
	float frame;
	Vector2D<float> pos;
	Vector2D<float> dir;
	int damage;
	int type;
	int velocity;
public:
	int GetDamage() { return damage; }
	Bullet(int type, Vector2D<float> pos, Vector2D<float> dir);
	void SetImage(int type);
	void draw_bullet(HDC mDC);
	void update();
	virtual void handle_collision(int otherLayer);
};