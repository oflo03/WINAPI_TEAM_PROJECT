#pragma once
#include<vector>
#include<cmath>
#include <atlImage.h>
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

struct Animation
{
	CImage resource;
	RECT size;
	int frame;
};

class Player
{
protected:
	Animation animation[6];
	int frame;
	double x;
	double y;
	int dirX;
	int dirY;
	int direction;
	bool isFront;
	PlayerState* state;
	int velocity;
	int horizonDir;
public:
	//virtual ~Player() = 0;
	virtual void draw_character(HDC mDC) = 0;
	virtual void handle_event() = 0;
	virtual void update() = 0;
	virtual void change_frame() = 0;
	virtual void SetImage(int state) = 0;
	void DestroyImage() { for (int i = 0; i < 6; i++) animation[i].resource.Destroy(); }
	bool& set_virtical() { return isFront; }
	int& set_horizon() { return horizonDir; }
	void SetX(double x) {this->x = x;}
	void SetY(double y) {this->y = y;}
	double GetX() { return x; }
	double GetY() { return y; }
	int GetDirX() { return dirX; }
	int GetDirY() { return dirY; }
	void SetDirX(int x) { this->dirX = x; }
	void SetDirY(int y) { this->dirY = y; }
	double GetVelocity() { return velocity; };
	int GetDirection() { return direction; }
};

