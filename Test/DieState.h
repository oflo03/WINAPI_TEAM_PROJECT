#pragma once
#include "BossState.h"
class DieState :
    public BossState
{
private:
    float time;
    float dirX;
public:
    DieState() { dirX = 0.01, time = 0; }
    virtual void enter(Boss& boss);
    virtual BossState* handle_event(Boss& boss);
    virtual void update(Boss& boss);
};

