#pragma once

#include<vector>
#include"Vector2D.h"
#include"Animation.h"
#include"State.h"
#include"Bullet.h"
#include"Weapon.h"
#include"Master.h"

extern RECT screen;

class Enemy : public Master
{
protected:
	float frame;
	float angle;
	Vector2D<float> pos;
	Vector2D<float> dir;
	int direction;
	PlayerState* state;
	double velocity;
public:
	Enemy(float x, float y) : pos(x, y), dir(0, 0), frame(0), angle(90), direction(FRONT), state(nullptr), velocity(200) {}
	Enemy() : pos(screen.right/2, screen.bottom/2), dir(0, 0), frame(0), angle(90), direction(FRONT), state(nullptr), velocity(200) {}
	Enemy(const Enemy& other) : pos(other.pos.x, other.pos.y), dir(0, 0), frame(0), angle(90), direction(FRONT), state(nullptr), velocity(200) {}
	virtual void draw_character(HDC mDC) = 0;
	virtual void handle_event() = 0;
	virtual void update() = 0;
	virtual void SetImage(int state) = 0;
	virtual void SetDirection() = 0;
	virtual void DestroyImage() = 0;
};
