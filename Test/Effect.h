#pragma once
#include"Animation.h"
#include"Vector2D.h"
#include<string>

extern double frame_time;

class Effect {
public:
	Animation effect;
	float time;
	Vector2D<float> pos;
	int velocity;
	Effect(std::wstring name, Vector2D<float> pos, int velocity, int frame);
	~Effect() { effect.resource.Destroy(); }
	void Draw(HDC mDC);
	void update();
	bool TimeOver() const {
		return ((int)time == effect.frame);
	}
};

