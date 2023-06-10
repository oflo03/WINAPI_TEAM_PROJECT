#pragma once
#include"Tilemap.h"
#define MapNum 2
#define MapWidth 30
#define MapHeight 17

#define TilePos Maps[i][j].tilePos
class MapManager
{
private:
	static MapManager* instance;
	CImage grassImage;
	CImage wallImage;
	Tile Maps[MapHeight][MapWidth];
	int currentStage;
	MapManager();
	~MapManager();
public:
	static MapManager* getInstance();
	static void release();
	void LoadTileMap(int stage);
	void PrintMap(HDC mDC);
	int	getCurStage() { return currentStage; }
};

