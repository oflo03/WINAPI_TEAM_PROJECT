#pragma once
#include <atlImage.h>
#include"Vector2D.h"
#include<vector>

enum ID // 아이템 추가할 때 여기 ID명 작성
{
	SWORD		// long sword
	, PISTOL	// semi-automatic pistol
	, RIFLE		// assault rifle
	, SHOTGUN	// double barrel shotgun
	, ROCKET	// rocket launcher
};

const int cooltime[]{ 30,15,7,30,10 };
const int rebound[]{ 30,15,7,30,10 };

class Item
{
protected:
	CImage resource[2];
};