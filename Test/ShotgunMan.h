#pragma once
#include "Enemy.h"
class ShotgunMan :
    public Enemy
{
private:
    static Animation animation[4][6];
    CImage hand;
    Vector2D<float> handPos;
    Weapon* weapon;
    float moveTime;
public:
    ShotgunMan(double x, double y, Player* target);
    ~ShotgunMan();
    static void init();
    static void release();
    virtual void draw_character(HDC mDC);
    virtual void handle_event();
    virtual void update();
    virtual void SetDirection();
    virtual void attack();
    virtual void handle_collision(int otherLayer, int damage);
};

