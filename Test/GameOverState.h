#pragma once
#include "game_framework.h"
class GameOverState :
    public GameState
{
protected:
    CImage back;
public:
    GameOverState();
    ~GameOverState();
    void update();
    void handle_events();
    void draw();
};

