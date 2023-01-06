#include "Map.h"
#include "Utils.h"
#include "Textures.h"
#include "Game.h"
#include "debug.h"

CMap::CMap(int TileSetID, int TotalRowsInMap, int TotalColumnsInMap, int RowsInTileSet, int ColumnsInTileSet, int TotalTiles, int** tileMatrix)
{
	TileTexture = CTextures::GetInstance()->Get(TileSetID);
	this->TotalRowsInMap = TotalRowsInMap;
	this->TotalColumnsInMap = TotalColumnsInMap;
	this->RowsInTileSet = RowsInTileSet;
	this->ColumnsInTileSet = ColumnsInTileSet;
	this->TotalTiles = TotalTiles;
	this->TileMap = tileMatrix;
}

CMap::~CMap()
{
}

void CMap::AddTiles()
{
	for (int tileID = 0; tileID < TotalTiles; tileID++)
	{
		int left = tileID % ColumnsInTileSet * TILE_WIDTH;
		int top = tileID / ColumnsInTileSet * TILE_HEIGHT;
		int right = left + TILE_WIDTH;
		int bottom = top + TILE_HEIGHT;
		LPSPRITE NewTile = new CSprite(tileID, left, top, right, bottom, TileTexture);
		this->Tiles.push_back(NewTile);
	}
}

void CMap::Render()
{
	//Get camera
	CGame* game = CGame::GetInstance();
	float cam_x, cam_y;
	game->GetCamPos(cam_x, cam_y);
	int cam_w = game->GetBackBufferWidth();
	int cam_h = game->GetBackBufferHeight();

	int BeginRow = (int)floor(cam_y / TILE_HEIGHT);
	int EndRow = (int)ceil((cam_y + cam_h) / TILE_HEIGHT);
	int BeginColumn = (int)floor(cam_x / TILE_WIDTH);
	int EndColumn = (int)ceil((cam_x + cam_w) / TILE_WIDTH);

	//Render
	for (int CurrentRow = BeginRow; CurrentRow < EndRow; CurrentRow++)
		for (int CurrentColumn = BeginColumn; CurrentColumn < EndColumn; CurrentColumn++)
		{
			int index = TileMap[CurrentRow][CurrentColumn] - 1;
			Tiles.at(index)->Draw((float)(CurrentColumn * TILE_WIDTH), (float)(CurrentRow * TILE_HEIGHT), "TILE");
		}
}

int CMap::GetMapWidth()
{
	return TotalColumnsInMap * TILE_WIDTH;
}

int CMap::GetMapHeight()
{
	return TotalRowsInMap * TILE_HEIGHT;
}