#pragma once
#include "game_framework.h"

class SelectState :
	public GameState
{
private:
	CImage background, cursor, image1, image2;
public:
	SelectState();
	~SelectState();
	virtual void update();
	virtual void handle_events();
	virtual void draw();
};

