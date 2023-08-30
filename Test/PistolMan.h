#pragma once
#include "Enemy.h"
class PistolMan :
    public Enemy
{
private:
    static Animation animation[4][6];
    CImage hand;
    Vector2D<float> handPos;
    Weapon* weapon;
    float moveTime;
public:
    PistolMan(double x, double y, Player* target);
    ~PistolMan();
    static void init();
    static void release();
    virtual void draw_character(HDC mDC);
    virtual void handle_event();
    virtual void SetDirection();
    virtual void attack();
    virtual void update();
    virtual void handle_collision(int otherLayer, int damage);
    virtual void CalWeight();
};

