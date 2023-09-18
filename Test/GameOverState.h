#pragma once
#include "game_framework.h"
class GameOverState :
    public GameState
{
protected:
    CImage back;
    CImage black;
    HFONT rom;
    int time;
    int dir;
    LONG alpha;
public:
    GameOverState();
    ~GameOverState();
    void update();
    void handle_events();
    void draw();
};

