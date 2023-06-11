#include"EffectManager.h"

Animation Effect::effect[16];

void Effect::init()
{
	effect[CEffect::PISTOLBULLET].resource.Load(L"resources/Bullet_Pistol_effect.png");
	effect[CEffect::PISTOLBULLET].frame = 4;
	effect[CEffect::PISTOLBULLET].velocity = 3;
	effect[CEffect::RIFLEBULLET].resource.Load(L"resources/Bullet_Rifle_effect.png");
	effect[CEffect::RIFLEBULLET].frame = 6;
	effect[CEffect::RIFLEBULLET].velocity = 3;
	effect[CEffect::SHOTGUNBULLET].resource.Load(L"resources/Bullet_Shotgun_effect.png");
	effect[CEffect::SHOTGUNBULLET].frame = 6;
	effect[CEffect::SHOTGUNBULLET].velocity = 3;
	effect[CEffect::ENEMYBULLET].resource.Load(L"resources/enemy_bullet_effect.png");
	effect[CEffect::ENEMYBULLET].frame = 5;
	effect[CEffect::ENEMYBULLET].velocity = 3;
	effect[CEffect::BOUNCEBULLET].resource.Load(L"resources/Bullet_bounce_effect.png");
	effect[CEffect::BOUNCEBULLET].frame = 5;
	effect[CEffect::BOUNCEBULLET].velocity = 3;
	effect[CEffect::SWORDATTACK].resource.Load(L"resources/melee_effect.png");
	effect[CEffect::SWORDATTACK].frame = 3;
	effect[CEffect::SWORDATTACK].velocity = 4;
	effect[CEffect::BOMBSHE1].resource.Load(L"resources/banshe_effect.png");
	effect[CEffect::BOMBSHE1].frame = 13;
	effect[CEffect::BOMBSHE1].velocity = 1;
	effect[CEffect::BOMBSHE2].resource.Load(L"resources/banshe_effect2.png");
	effect[CEffect::BOMBSHE2].frame = 3;
	effect[CEffect::BOMBSHE2].velocity = 2.5;
	effect[CEffect::BATDIE].resource.Load(L"resources/bat_explosion.png");
	effect[CEffect::BATDIE].frame = 5;
	effect[CEffect::BATDIE].velocity = 3;
	effect[CEffect::BOMBSHEDIE].resource.Load(L"resources/Bombshe_explode.png");
	effect[CEffect::BOMBSHEDIE].frame = 5;
	effect[CEffect::BOMBSHEDIE].velocity = 3;
	effect[CEffect::SHOTGUNDIE].resource.Load(L"resources/enemy_shotgun_explode.png");
	effect[CEffect::SHOTGUNDIE].frame = 4;
	effect[CEffect::SHOTGUNDIE].velocity = 4;
	effect[CEffect::DAMAGED].resource.Load(L"resources/player_damaged.png");
	effect[CEffect::DAMAGED].frame = 5;
	effect[CEffect::DAMAGED].velocity = 4;
	effect[CEffect::PATTERNA].resource.Load(L"resources/boss_patternA.png");
	effect[CEffect::PATTERNA].frame = 8;
	effect[CEffect::PATTERNA].velocity = 3;
	effect[CEffect::PATTERNB].resource.Load(L"resources/boss_patternB.png");
	effect[CEffect::PATTERNB].frame = 7;
	effect[CEffect::PATTERNB].velocity = 4;
	effect[CEffect::PATTERNC].resource.Load(L"resources/boss_patternC.png");
	effect[CEffect::PATTERNC].frame = 9;
	effect[CEffect::PATTERNC].velocity = 2;
	effect[CEffect::PATTERND].resource.Load(L"resources/boss_patternD.png");
	effect[CEffect::PATTERND].frame = 6;
	effect[CEffect::PATTERND].velocity = 2;
	for (int i = 0; i < 16; i++) {
		effect[i].size = { 0,0,effect[i].resource.GetWidth() / effect[i].frame, effect[i].resource.GetHeight() };
	}
}
void Effect::destroy()
{
	for (int i = 0; i < 16; i++)
		effect[i].resource.Destroy();
}

void Effect::Draw(HDC mDC) {
	effect[type].resource.Draw(mDC, pos.x - effect[type].size.right, pos.y - effect[type].size.bottom, effect[type].size.right * 2, effect[type].size.bottom * 2,
		(int)time * effect[type].size.right, 0, effect[type].size.right, effect[type].size.bottom);
}

void Effect::update() {
	time = (time + frame_time * effect[type].velocity * effect[type].frame);
}

