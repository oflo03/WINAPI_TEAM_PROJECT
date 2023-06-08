#pragma once
#include "Enemy.h"
class Bombshe :
    public Enemy
{
private:
    Animation animation[6];
    int attackSize;
    float moveTime;
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

