#pragma once
#include "State.h"
class RunState :
    public PlayerState
{
    virtual ~RunState();
    virtual PlayerState* handle_event(Player& player);
    virtual void update(Player& player);
    virtual void enter(Player& player);
    virtual void exit(Player& player);
};

