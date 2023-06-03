#pragma once
#include "Enemy.h"
class PistolMan :
    public Enemy
{
private:
    Animation animation[4];
    CImage hand;
    Vector2D<float> handPos;
    std::vector<Bullet*> myBullets;
    Weapon* weapon;
public:
    PistolMan(double x, double y);
    PistolMan(const PistolMan& other);
    PistolMan();
};

