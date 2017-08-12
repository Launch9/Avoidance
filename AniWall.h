#pragma once
#include "Basic_Tile_MOTHER.h"
class AniWall : public Basic_Tile_MOTHER
{
public:
	AniWall(int ID, int x_pos, int y_pos, TileMap &TM);
	static void Addline(unsigned int ID, int x, int y, int direction, int distance, TileMap &TM);
};

