#pragma once
#include"Master.h"
#include<atlimage.h>
#include<fstream>

CImage grassImage;
CImage wallImage;

void LoadTileMap();
void PrintMap(HDC mDC);

enum tileType
{
	none, grass, wall_t
};

struct Tile
	:public Master
{
	int type;
	int tilePos;
	friend std::ifstream& operator>>(std::ifstream& is, Tile& tile);
	virtual void handle_collision(int otherLayer, int damage) {};
};