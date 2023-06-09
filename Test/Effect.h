#pragma once
#include"Animation.h"
#include"Vector2D.h"
#include<string>

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
	DAMAGED
	//이펙트 추가는 여기서
};

class Effect {
public:
	static Animation effect[12];
	int type;
	float time;
	Vector2D<float> pos;
	Effect(const CEffect& type, Vector2D<float> pos) : type(type), pos(pos), time(0) {}
	~Effect() {  }
	static void init();
	void Draw(HDC mDC);
	void update();
	bool TimeOver() const {
		return ((int)time == effect[type].frame);
	}
};

