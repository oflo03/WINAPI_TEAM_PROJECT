#pragma once
#include"Animation.h"
#include"Vector2D.h"
#include"Master.h"
#include"Item.h"

const int BulletDamage[]{ 10,7,5,5,3,30,10,10,10,10,10,10,10 };

enum bullet_table {
	BPISTOL,
	BRIFLE,
	BSHOTGUN,
	BENEMY,
	BBOUNCE,
	BOSSBULLET1,
	BOSSBULLET2,
	BOSSBULLET3,
	BOUNCEDBOSSBULLET2,
	BROCKET
};

class Bullet
	:public Master
{
protected:
	static Animation animation[10];
	int type;
	int side;
	float frame;
	Vector2D<float> pos;
	Vector2D<float> dir;
	double velocity;
	double angle;
public:
	Bullet(int type, int side, Vector2D<float> pos, Vector2D<float> dir);
	~Bullet();
	static void init();
	void draw_bullet(HDC mDC);
	void update();
	virtual void handle_collision(int otherLayer, int damage);
};