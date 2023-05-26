#pragma once
#include "State.h"
class RollState :
    public PlayerState
{
private:
    int rollingTime;
    Vector2D<float> dir;
public:
    RollState(float dirX,float dirY): dir(dirX,dirY) { rollingTime = 0; }
    virtual ~RollState();
    virtual PlayerState* handle_event(Player& player);
    virtual void update(Player& player);
    virtual void enter(Player& player);
    virtual void exit(Player& player);
 
};

