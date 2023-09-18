#pragma once
#include"Animation.h"
#include"Vector2D.h"
#include<string>
#define AMOUNT 19

extern double frame_time;

enum CEffect {
	PISTOLBULLET,
	RIFLEBULLET,
	SHOTGUNBULLET,
	ENEMYBULLET,
	BOUNCEBULLET,
	SWORDATTACK,
	BOMBSHE1,
	BOMBSHE2,
	BATDIE,
	BOMBSHEDIE,
	SHOTGUNDIE,
	DAMAGED,
	PATTERNA,
	PATTERNB,
	PATTERNC,
	PATTERND,
	EXPLOSION,
	BOSSHIT,
	TELEPORT
};

class Effect {
public:
	static Animation effect[AMOUNT];
	int type;
	float time;
	Vector2D<float> pos;
	Effect(const CEffect& type, Vector2D<float> pos) : type(type), pos(pos), time(0) {}
	~Effect() {  }
	static void init();
	static void destroy();
	void Draw(HDC mDC);
	void update();
	bool TimeOver() const {
		return ((int)time == effect[type].frame);
	}
};

