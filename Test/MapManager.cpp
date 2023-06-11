#include "MapManager.h"

MapManager* MapManager::instance = nullptr;

MapManager::MapManager()
{
	currentStage = 1;
	grassImage.Load(L"Tiles_Grass.png");
	wallImage.Load(L"Tiles_Wall.png");
}


MapManager::~MapManager()
{
	grassImage.Destroy();
	wallImage.Destroy();
}

MapManager* MapManager::getInstance()
{
	if (instance == nullptr)
		instance = new MapManager;
	return instance;
}

void MapManager::release()
{
	if (instance != nullptr)
		delete instance;
	instance = nullptr;
}

void MapManager::LoadTileMap(int stage)
{
	currentStage = stage;
	std::ifstream mapFile;
	switch (currentStage)
	{
	case 1:
		mapFile = std::ifstream{ "map1.txt" };
		break;
	case 2:
		mapFile = std::ifstream{ "map2.txt" };
		break;
	case 3:
		mapFile = std::ifstream{ "map3.txt" };
		break;
	case 4:
		mapFile = std::ifstream{ "map4.txt" };
		break;
	default:
		return;
	}
	for (int i = 0; i < MapHeight; ++i)
		for (int j = 0; j < MapWidth; ++j)
		{
			mapFile >> Maps[i][j];
			if (Maps[i][j].type == wall_t)
				Maps[i][j].col->pos = Vector2D<float>(j * PTS + TileSize, i * PTS + TileSize);
		}
}

void MapManager::PrintMap(HDC mDC)
{
	for (int i = 0; i < MapHeight; ++i)
		for (int j = 0; j < MapWidth; ++j)
			switch (Maps[i][j].type)
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
