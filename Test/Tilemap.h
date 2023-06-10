#pragma once
#include"Master.h"
#include<atlimage.h>
#include<fstream>

#define TileSize 32
#define PrintTileSize (TileSize * 2)
#define PTS PrintTileSize
#define GrassTileNum 8
#define WallTileNum 16

enum tileType
{
	none, grass, wall_t
};

class Tile
	:public Master
{
private:
	friend std::ifstream& operator>>(std::ifstream& is, Tile& tile);
public:
	int type;
	int tilePos;
	virtual void handle_collision(int otherLayer, int damage) {};
};

