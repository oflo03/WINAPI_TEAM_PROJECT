#include"Tilemap.h"

int SelectedMap;

#define MapNum 1
#define MapWidth 10
#define MapHeight 10

#define TileWidth 32
#define PrintTileWidth (TileWidth * 2)
#define PTW PrintTileWidth

#define TileHeight 32
#define PrintTileHeight (TileHeight * 2)
#define PTH PrintTileHeight
#define TilePos Maps[SelectedMap][i][j].tilePos

Tile Maps[MapNum][MapHeight][MapWidth];

void LoadTileMap()
{
	grassImage.Load(L"Tiles_Grass.png");
	wallImage.Load(L"Tiles_Wall.png");
	std::ifstream mapFile{ "maps.txt" };
	for (int m = 0; m < MapNum; ++m)
		for (int i = 0; i < MapHeight; ++i)
			for (int j = 0; j < MapWidth; ++j)
				mapFile >> Maps[m][i][j];
	SelectedMap = 0;
}

void PrintMap(HDC mDC)
{
	for (int i = 0; i < MapHeight; ++i)
		for (int j = 0; j < MapWidth; ++j)
			switch (Maps[SelectedMap][i][j].type)
			{
			case grass:
				grassImage.StretchBlt(mDC, i * PTW, j * PTH, PTW, PTH,
					TilePos % MapWidth * TileWidth, TilePos / MapWidth * TileHeight, TileWidth, TileHeight, SRCCOPY);
				break;
			case wall_t:
				wallImage.StretchBlt(mDC, i * PTW, j * PTH, PTW, PTH,
					TilePos % MapWidth * TileWidth, TilePos / MapWidth * TileHeight, TileWidth, TileHeight, SRCCOPY);
				break;
			default:
				break;
			}
}
std::ifstream& operator>>(std::ifstream& is, Tile& tile)
{
	is >> tile.type, is >> tile.tilePos;
	return is;
}

void Tile::handle_collision(int otherLayer) {}