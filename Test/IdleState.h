#pragma once
#include "State.h"
class IdleState :
    public PlayerState
{
public:
    virtual ~IdleState();
    virtual PlayerState* handle_event(Player& player);
    virtual void update(Player& player);
    virtual void enter(Player& player);
};

