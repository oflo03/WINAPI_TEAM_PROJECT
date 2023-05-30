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
	, GRENADE	// hand grenade

};

const int cooltime[]{ 10,10,7,10,10,10 };

class Item
{
protected:
	CImage resource;
};