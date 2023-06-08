#pragma once
#include "Enemy.h"
class Bat :
    public Enemy
{
private:
    static Animation animation[2];
public:
    Bat(double x, double y, Player* target);
    ~Bat();
    static void init();
    static void release();
    virtual void draw_character(HDC mDC);
    virtual void handle_event();
    virtual void update();
    virtual void SetDirection();
    virtual void attack();
    virtual void handle_collision(int otherLayer, int damage);
};

