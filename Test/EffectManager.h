#pragma once
#include<vector>
#include<memory>
#include"Effect.h"

class Effect;

class EffectManager {
private:
	std::vector<std::unique_ptr<Effect>> effect;
	static EffectManager* instance;
	EffectManager() {}
	~EffectManager() {
		effect.clear();
	}
public:
	static EffectManager* getInstance();
	static void init();
	static void Destroy();
	void Draw(HDC mDC);
	void update();
	void set_effect(Effect* e);
	void delete_effect();
};

