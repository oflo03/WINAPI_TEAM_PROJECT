#include"Tilemap.h"

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