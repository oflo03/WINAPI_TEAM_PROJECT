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
	CImage Poke_grassImage;
	CImage Poke_waterImage;
	Tile Maps[MapHeight][MapWidth];
	int currentStage;
	MapManager();
	~MapManager();
public:
	static MapManager* getInstance();
	void LoadTileMap(int stage);
	void PrintMap(HDC mDC);
	int	getCurStage() { return currentStage; }
};

