#pragma once
#include"Master.h"
#include"Player.h"
#include"BossState.h"

extern RECT screen;

enum HAND{
	LEFT,RIGHT
};

class BossState;

class Boss : public Master
{
private:
	static Boss* instance;
	Animation body;
	Animation hand[2];
	CImage shadow;
	BossState* state;
	int HP;
	Boss();
	~Boss();
public:
	Player* target;
	CImage warning;
	Vector2D<float> pos;
	Vector2D<float> handPos[2];
	int lastPattern;
	float frame;
	float angle[2];
	int handType[2];
	static Boss* getInstance();
	static void release();
	void draw(HDC mDC);
	void handle_event();
	void update();
	void handle_collision(int otherLayer, int damage);
};

