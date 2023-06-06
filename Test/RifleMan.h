#pragma once
#include "Enemy.h"

class RifleMan :
    public Enemy
{
private:
    Animation animation[6];
    CImage hand;
    Vector2D<float> handPos;
    Weapon* weapon;
    float moveTime;
public:
    RifleMan(double x, double y, Player* target);
    ~RifleMan();
    virtual void draw_character(HDC mDC);
    virtual void handle_event();
    virtual void update();
    virtual void SetImage(int state);
    virtual void SetDirection();
    virtual void attack();
    virtual void DestroyImage();
    virtual void handle_collision(int otherLayer, int damage);
};

