#pragma once
#include "Basic_Tile_MOTHER.h"
class SaveStation: public Basic_Tile_MOTHER
{
public:

	SaveStation(int x_pos, int y_pos, TileMap &TM);
	bool ifCollision(int PlayerChannel);
};

