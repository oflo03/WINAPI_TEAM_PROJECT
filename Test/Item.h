#pragma once
#include <atlImage.h>

enum ID // ������ �߰��� �� ���� ID�� �ۼ�
{
	SWORD		// long sword
	, PISTOL	// semi-automatic pistol
	, RIFLE		// assault rifle
	, SHOTGUN	// double barrel shotgun
	, ROCKET	// rocket launcher
	, GRENADE	// hand grenade

};

class Item
{
protected:
	CImage resource;
};