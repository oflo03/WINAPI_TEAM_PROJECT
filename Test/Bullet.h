#pragma once
#include"Animation.h"
#include"Vector2D.h"
#include"Master.h"

const int BulletDamage[]{ 0,10,7,4 ,5};

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
	int side;
	double velocity;
	double angle;
public:
	int GetDamage() { return damage; }
	Bullet(int type, int side, Vector2D<float> pos, Vector2D<float> dir);
	~Bullet();
	void SetImage(int type);
	void draw_bullet(HDC mDC);
	void update();
	virtual void handle_collision(int otherLayer);
};