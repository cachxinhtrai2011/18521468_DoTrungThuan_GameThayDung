#include "Map.h"
#include "Utils.h"
#include "Textures.h"
#include "Game.h"
#include "debug.h"
#include "Sprites.h"

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
	ifstream f;
	f.open(path);

	// current resource section flag
	int section = MAP_UNKNOWN_SECTION;
	char str[MAX_MAP_LINE];
	while (f.getline(str, MAX_MAP_LINE)) {
		string line(str);
		if (line[0] == '#') continue;
		if (line == "[Info]") {
			section = MAP_INFO_SECTION;
			continue;
}
		if (line == "[Map]") {
			section = MAP_TILE_SECTION;
			continue;
		}
		if (line[0] == '[') {
			section = MAP_UNKNOWN_SECTION;
			continue;
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
	f.close();
	LoadMapTiles();
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

void CMap::_ParseSection_Info(string line)
{
	vector<string> tokens = split(line);
	size_t size = tokens.size();

	if (size < 5) return;
	row = atoi(tokens[0].c_str());
	column = atoi(tokens[1].c_str());
	tileRow = atoi(tokens[2].c_str());
	tileColumn = atoi(tokens[3].c_str());
	tileSize = atoi(tokens[4].c_str());
	tex = CTextures::GetInstance()->Get(atoi(tokens[5].c_str()));
	height = row * tileSize;
	width = column * tileSize;

	offsetW = CGame::GetInstance()->GetBackBufferWidth() / tileSize + EXTRA_TILE;
	offsetH = CGame::GetInstance()->GetBackBufferHeight() / tileSize + EXTRA_TILE;
}

int CMap::GetMapWidth()
{
	return TotalColumnsInMap * TILE_WIDTH;
}

int CMap::GetMapHeight()
{
	return TotalRowsInMap * TILE_HEIGHT;
}