#pragma once
#include "Player.h"

class UI
{
protected:
public:
	static void init();
	static void Destroy();
	static void draw(HDC mDC);
};