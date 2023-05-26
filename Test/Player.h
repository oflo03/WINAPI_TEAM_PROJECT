#pragma once
#include<vector>
#include"Vector2D.h"
#include"Animation.h"
#include"State.h"

class PlayerState;

enum STATE
{
	STATE_IDLE, STATE_RUN, STATE_ROLL
};

enum DIRECTION
{
	FRONT,FRONT_RIGHT,FRONT_LEFT, BACK,BACK_RIGHT,BACK_LEFT
};

class Player
{
protected:
	Animation animation[6];
	int frame;
	Vector2D<float> pos;
	Vector2D<float> dir;
	int direction;
	bool isFront;
	PlayerState* state;
	int velocity;
	int horizonDir;
public:
	Player(float x, float y) : pos(x,y) , dir(0,0), frame(0), direction(FRONT), isFront(true), horizonDir(0),state(nullptr),  velocity(300) {}
	Player() : pos(400, 300), dir(0, 0), frame(0), direction(FRONT), isFront(true), horizonDir(0), state(nullptr), velocity(300) {}
	virtual void draw_character(HDC mDC) = 0;
	virtual void handle_event() = 0;
	virtual void update() = 0;
	virtual void change_frame() = 0;
	virtual void SetImage(int state) = 0;
	void DestroyImage() { for (int i = 0; i < 6; i++) animation[i].resource.Destroy(); }
	bool& set_virtical() { return isFront; }
	int& set_horizon() { return horizonDir; }
	void SetPos(Vector2D<float> temp) { pos = temp; }
	Vector2D<float> GetPos() { return pos; }
	void SetDir(Vector2D<float> temp) { dir = temp; }
	Vector2D<float> GetDir() { return dir; }
	double GetVelocity() { return velocity; };
	int GetDirection() { return direction; }
};

