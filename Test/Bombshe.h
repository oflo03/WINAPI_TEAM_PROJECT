#pragma once
#include "Enemy.h"
#include "EffectManager.h"

class Bombshe :
    public Enemy
{
private:
    Animation animation[6];
    float attackSize;
    float moveTime;
    Effect* wave;
    bool isAttack;
public:
    Bombshe(double x, double y, Player* target);
    ~Bombshe();
    virtual void draw_character(HDC mDC);
    virtual void handle_event();
    virtual void update();
    virtual void SetImage(int state);
    virtual void SetDirection();
    virtual void attack();
    virtual void DestroyImage();
    virtual void handle_collision(int otherLayer, int damage);
};

