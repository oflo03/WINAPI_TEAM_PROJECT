#include"EffectManager.h"

Effect::Effect(std::wstring name, Vector2D<float> pos, int velocity, int frame) : pos(pos) {
	effect.resource.Load(name.c_str());
	effect.frame = frame;
	effect.size = { 0,0,effect.resource.GetWidth() / effect.frame ,effect.resource.GetHeight() };
	time = 0;
	this->velocity = velocity;
}

void Effect::Draw(HDC mDC) {
	effect.resource.Draw(mDC, pos.x - effect.size.right, pos.y - effect.size.bottom, effect.size.right * 2, effect.size.bottom * 2,
		(int)time * effect.size.right, 0, effect.size.right, effect.size.bottom);
}

void Effect::update() {
	time = (time + frame_time * velocity * effect.frame);
}

