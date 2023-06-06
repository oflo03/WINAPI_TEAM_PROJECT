#include"Tilemap.h"

int SelectedMap;

#define MapNum 1
#define MapWidth 30
#define MapHeight 17

#define TileSize 32
#define PrintTileSize (TileSize * 2)
#define PTS PrintTileSize
#define TilePos Maps[SelectedMap][i][j].tilePos

#define GrassTileNum 8
#define WallTileNum 16

Tile Maps[MapNum][MapHeight][MapWidth];

void LoadTileMap()
{
	grassImage.Load(L"Tiles_Grass.png");
	wallImage.Load(L"Tiles_Wall.png");
	std::ifstream mapFile{ "maps.txt" };
	for (int m = 0; m < MapNum; ++m)
		for (int i = 0; i < MapHeight; ++i)
			for (int j = 0; j < MapWidth; ++j)
			{
				mapFile >> Maps[m][i][j];
				if (Maps[m][i][j].type == wall_t)
					Maps[m][i][j].col->pos = Vector2D<float>(j * PTS + TileSize, i * PTS + TileSize);
			}
	SelectedMap = 0;
}

void PrintMap(HDC mDC)
{
	for (int i = 0; i < MapHeight; ++i)
		for (int j = 0; j < MapWidth; ++j)
			switch (Maps[SelectedMap][i][j].type)
			{
			case grass:
				grassImage.TransparentBlt(mDC, j * PTS, i * PTS, PTS, PTS,
					TilePos % GrassTileNum * TileSize, TilePos / GrassTileNum * TileSize, TileSize, TileSize, RGB(255, 255, 255));
				break;
			case wall_t:
				wallImage.TransparentBlt(mDC, j * PTS, i * PTS, PTS, PTS,
					TilePos % WallTileNum * TileSize, TilePos / WallTileNum * TileSize, TileSize, TileSize, RGB(255, 255, 255));
				break;
			default:
				break;
			}
}
std::ifstream& operator>>(std::ifstream& is, Tile& tile)
{
	is >> tile.type, is >> tile.tilePos;
	if (tile.type == wall_t)
	{
		tile.col = new Collider(Vector2D<float>(TileSize, TileSize));
		tile.col->owner = &tile;
		tile.col->layer = wall;
		COLL.emplace_back(tile.col);
	}
	return is;
}