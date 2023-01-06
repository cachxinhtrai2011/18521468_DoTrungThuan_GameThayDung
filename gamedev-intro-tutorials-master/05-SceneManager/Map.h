#pragma once
#include "Sprites.h"

#define TILE_WIDTH 16
#define TILE_HEIGHT 16

class CMap
{
	int TotalRowsInMap, TotalColumnsInMap;
	int RowsInTileSet, ColumnsInTileSet;
	int TotalTiles;
	LPTEXTURE TileTexture;
	vector<LPSPRITE> Tiles;
	int** TileMap;
public:
	CMap(int TileSetID, int TotalRowsInMap, int TotalColumnsInMap, int RowsInTileSet, int ColumnsInTileSet, int TotalTiles, int** tileMatrix);
	~CMap();
	void Render();
	void AddTiles();
	int GetMapWidth();
	int GetMapHeight();
};