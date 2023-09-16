#pragma once
#include"Animation.h"
#include"Vector2D.h"

class Portal
{
protected:
	static Portal* instance;
	Animation portal, E, P;
	float pframe, eframe;
	Vector2D<float> pos;
	Portal(float x, float y) :pos(x, y), pframe(0), eframe(0) {
		portal.resource.Load(L"resources/Portal.png");
		portal.frame = 4;
		portal.velocity = 1;
		portal.size = { 0,0,portal.resource.GetWidth() / portal.frame, portal.resource.GetHeight() };
		E.resource.Load(L"resources/Portal_E-Key.png");
		E.frame = 2;
		E.velocity = 1;
		E.size = { 0,0,E.resource.GetWidth() / E.frame, E.resource.GetHeight() };
		P.resource.Load(L"resources/Portal_P-Key.png");
		P.frame = 2;
		P.velocity = 1;
		P.size = { 0,0,P.resource.GetWidth() / P.frame, P.resource.GetHeight() };
	}
	~Portal() {
		portal.resource.Destroy();
		E.resource.Destroy();
		P.resource.Destroy();
	}
public:
	Vector2D<float> GetPos() { return pos; };
	static Portal* getInstance();
	static void release();
	void SetPos(Vector2D<float> point) { pos = point; }
	void update();
	void handle_event();
	void Draw(HDC mDC);
};