#include"Tilemap.h"

std::ifstream& operator>>(std::ifstream& is, Tile& tile)
{
	is >> tile.type, is >> tile.tilePos;
	switch (tile.type)
	{
	case wall_t:
		tile.col = new Collider(Vector2D<float>(TileSize, TileSize));
		tile.col->owner = &tile;
		tile.col->layer = wall;
		COLL.emplace_back(tile.col);
		break;
	case poke_water:
		tile.col = new Collider(Vector2D<float>(TileSize, TileSize));
		tile.col->owner = &tile;
		tile.col->layer = water;
		COLL.emplace_back(tile.col);
		break;
	default:
		break;
	}
	return is;
}