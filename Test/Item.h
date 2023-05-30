#pragma once
#include <atlImage.h>
#include"Vector2D.h"
#include<vector>

enum ID // ������ �߰��� �� ���� ID�� �ۼ�
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