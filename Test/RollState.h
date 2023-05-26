#pragma once
#include "State.h"
class RollState :
    public PlayerState
{
private:
    int rollingTime;
    int dirX;
    int dirY;
public:
    RollState(int dirX,int dirY): dirX(dirX),dirY(dirY) { rollingTime = 0; }
    virtual ~RollState();
    virtual PlayerState* handle_event(Player& player);
    virtual void update(Player& player);
    virtual void enter(Player& player);
    virtual void exit(Player& player);
 
};

