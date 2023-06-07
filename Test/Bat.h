#pragma once
#include "Enemy.h"
class Bat :
    public Enemy
{
private:
    Animation animation;
public:
    Bat(double x, double y, Player* target);
    ~Bat();
    virtual void draw_character(HDC mDC);
    virtual void handle_event();
    virtual void update();
    virtual void SetImage(int state);
    virtual void attack();
    virtual void DestroyImage();
    virtual void handle_collision(int otherLayer, int damage);
};

