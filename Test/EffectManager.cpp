#include "EffectManager.h"

EffectManager* EffectManager::getInstance()
{
    if (instance == nullptr)
        instance = new EffectManager;
    return instance;
}

void EffectManager::Draw(HDC mDC)
{
    for (auto& e : effect)
        e->Draw(mDC);
}

void EffectManager::update()
{
    for (auto& e : effect)
       e->update();
}

void EffectManager::set_effect(Effect* e)
{
    effect.emplace_back(e);
}

void EffectManager::delete_effect()
{
    effect.erase(std::remove_if(effect.begin(), effect.end(), [](const std::unique_ptr<Effect>& effect) {return effect->TimeOver(); }), effect.end());
}

void EffectManager::clear()
{
    effect.clear();
}

EffectManager* EffectManager::instance = nullptr;
