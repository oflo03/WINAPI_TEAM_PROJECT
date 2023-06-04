#pragma once
#include "Enemy.h"
class PistolMan :
    public Enemy
{
private:
    Animation animation[6];
    CImage hand;
    Vector2D<float> handPos;
    Weapon* weapon;
public:
    PistolMan(double x, double y);
    PistolMan(const PistolMan& other);
    ~PistolMan();
    virtual void draw_character(HDC mDC);
    virtual void handle_event();
    virtual void update();
    virtual void SetImage(int state);
    virtual void SetDirection();
    virtual void attack();
    virtual void DestroyImage();
};

