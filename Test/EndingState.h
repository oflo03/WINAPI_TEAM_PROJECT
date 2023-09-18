#pragma once
#include "game_framework.h"
class EndingState :
    public GameState
{
protected:
    CImage back;
    HFONT rom;
public:
    EndingState();
    ~EndingState();
    void update();
    void handle_events();
    void draw();
};

