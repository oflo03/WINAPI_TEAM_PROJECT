#pragma once
#include"Animation.h"
#include"Vector2D.h"
#include<string>
#include"EffectManager.h"

extern double frame_time;

enum OBJECTTYPE {
	PLAYER,PISTOLMAM,RIFLEMAN,SHOTGUNMAN,BAT
};

class EffectManager;

class Effect {
public:
	Animation effect;
	float time;
	Vector2D<float> pos;
	int velocity;
	Effect(std::wstring name, Vector2D<float> pos, int velocity,int frame) : pos(pos){
		effect.resource.Load(name.c_str());
		effect.frame = frame;
		effect.size = { 0,0,effect.resource.GetWidth() / effect.frame ,effect.resource.GetHeight() };
		time = 0;
		this->velocity = velocity;
	}
	virtual ~Effect() { effect.resource.Destroy(); }
	virtual void Draw(HDC mDC) = 0;
	virtual void update() = 0;
	bool TimeOver() const {
		return ((int)time == effect.frame);
	}
};




class Particle :
	public Effect
{
public:
	Particle(std::wstring name, Vector2D<float> pos, int velocity, int frame) : Effect(name, pos, velocity, frame) {}
	virtual ~Particle() { effect.resource.Destroy(); }
	virtual void Draw(HDC mDC) {
		effect.resource.Draw(mDC, pos.x - effect.size.right, pos.y - effect.size.bottom, effect.size.right*2, effect.size.bottom*2,
			(int)time * effect.size.right, 0, effect.size.right, effect.size.bottom);
	}
	virtual void update() {
		time = (time + frame_time * velocity * effect.frame);
	}
};


class DieMotion :
	public Effect
{
public:
	int type;
	DieMotion(int type, std::wstring name, Vector2D<float> pos, int velocity, int frame) : Effect(name, pos, velocity, frame), type(type) {}
	virtual ~DieMotion() {
		switch (type)
		{
		case PLAYER:
			break;
		case PISTOLMAM:
			break;
		case RIFLEMAN:
			break;
		case SHOTGUNMAN:
			break;
		case BAT:
			//EffectManager::getInstance()->set_effect(new Particle(L"bat_explosion.png", pos, 3, 5));
			break;
		default:
			break;
		}
	}
	virtual void Draw(HDC mDC) {
		float yDest = pos.y - (effect.size.bottom - 20) * 2;
		effect.resource.Draw(mDC, pos.x - effect.size.right, yDest - 20, effect.size.right * 2, effect.size.bottom * 2,
			(int)time * effect.size.right, 0, effect.size.right, effect.size.bottom);
	}
	virtual void update() {
		time = (time + frame_time * velocity * effect.frame);
	}
};