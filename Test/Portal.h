#pragma once
#include"Animation.h"
#include"Vector2D.h"

class Portal
{
protected:
	static Portal* instance;
	Animation portal, E;
	float pframe, eframe;
	Vector2D<float> pos;
public:
	Portal(float x, float y) :pos(x, y), pframe(0), eframe(0) {
		portal.resource.Load(L"Portal.png");
		portal.frame = 4;
		portal.velocity = 1;
		portal.size = { 0,0,portal.resource.GetWidth() / portal.frame, portal.resource.GetHeight() };
		E.resource.Load(L"Portal_E-Key.png");
		E.frame = 2;
		E.velocity = 1;
		E.size = { 0,0,E.resource.GetWidth() / E.frame, E.resource.GetHeight() };
	}
	~Portal() {
		portal.resource.Destroy();
		E.resource.Destroy();
	}
	Vector2D<float> GetPos() { return pos; };
	static Portal* getInstance();
	void SetPos(Vector2D<float> point) { pos = point; }
	void update();
	void handle_event();
	void Draw(HDC mDC);
};