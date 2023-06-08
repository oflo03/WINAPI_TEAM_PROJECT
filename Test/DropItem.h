#pragma once
#include"Master.h"
#include"Animation.h"
#include"Item.h"

extern enum ID;

class DropItem
{
private:
	int type;
	Animation image;
	Vector2D<float> pos;
public:
	DropItem(int type, Vector2D<float> pos) : type(type),pos(pos) 
	{
		switch (type)
		{
		case PISTOL:
			image.resource.Load(L"drop_pistol.png");
			break;
		case RIFLE:
			image.resource.Load(L"drop_rifle.png");
			break;
		case SHOTGUN:
			image.resource.Load(L"drop_shotgun.png");
			break;
		default:
			break;
		}
	}

};

