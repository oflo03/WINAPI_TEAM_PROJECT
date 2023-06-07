#pragma once
#include"Animation.h"
#include"Vector2D.h"
#include"Master.h"
#include"Item.h"

const int BulletDamage[]{ 10,10,7,5 ,30 };

class Bullet
	:public Master
{
protected:
	Animation animation;
	int type;
	float frame;
	Vector2D<float> pos;
	Vector2D<float> dir;
	double velocity;
	double angle;
public:
	Bullet(int type, int side, Vector2D<float> pos, Vector2D<float> dir);
	~Bullet();
	void SetImage(int type);
	void draw_bullet(HDC mDC);
	void update();
	virtual void handle_collision(int otherLayer, int damage);
};