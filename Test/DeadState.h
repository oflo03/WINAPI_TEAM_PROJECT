#pragma once
#include "State.h"
class DeadState :
    public PlayerState
{
    virtual ~DeadState();
    virtual PlayerState* handle_event(Player& player);
    virtual void update(Player& player);
    virtual void enter(Player& player);
};

