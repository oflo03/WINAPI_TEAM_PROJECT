#pragma once
#include "Enemy.h"
#include "EffectManager.h"

class Bombshe :
    public Enemy
{
private:
    static Animation animation[4][3];
    float attackSize;
    float moveTime;
    Effect* wave;
    bool isAttack;
public:
    Bombshe(double x, double y, Player* target);
    ~Bombshe();
    static void init();
    static void release();
    virtual void draw_character(HDC mDC);
    virtual void handle_event();
    virtual void update();
    virtual void SetDirection();
    virtual void attack();
    virtual void handle_collision(int otherLayer, int damage);
    virtual void CalWeight();
};

