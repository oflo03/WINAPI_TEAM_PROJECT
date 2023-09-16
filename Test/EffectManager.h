#pragma once
#include<vector>
#include<memory>
#include"Effect.h"

class Effect;

class EffectManager {
private:
	std::vector<std::unique_ptr<Effect>> effect;
	static EffectManager* instance;
	EffectManager() { Effect::init(); }
	~EffectManager() {
		effect.clear();
		instance = nullptr;
		Effect::destroy();
	}
public:
	static EffectManager* getInstance();
	void Draw(HDC mDC);
	void update();
	void set_effect(Effect* e);
	void delete_effect();
	void clear();
};

