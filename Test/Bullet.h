#pragma once
#include"Animation.h"
#include"Vector2D.h"
#include"Master.h"

const int BulletDamage[]{ 20,10,7,5 ,30};

class Bullet
	:public Master
{
protected:
	Animation animation;
	float frame;
	Vector2D<float> pos;
	Vector2D<float> dir;
	double velocity;
	double angle;
	bool isInvalid;
public:
	Bullet(int type, int side, Vector2D<float> pos, Vector2D<float> dir);
	~Bullet();
	void SetImage(int type);
	void draw_bullet(HDC mDC);
	void update();
	virtual void handle_collision(int otherLayer, int damage);
};