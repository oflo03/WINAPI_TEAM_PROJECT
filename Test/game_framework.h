#pragma once

#include<vector>
#include<Windows.h>
#include<atlImage.h>

class GameState {
private:
public:
	GameState() = default;
	virtual ~GameState() = default;
	virtual void update() = 0;
	virtual void handle_events() = 0;
	virtual void draw() = 0;
};

void change_state(GameState* state);
void push_state(GameState* state);
void pop_state();
void start_game(GameState* state);
void end_game();