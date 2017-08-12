#pragma once
#include "Basic_Tile_MOTHER.h"
class Foreground: public Basic_Tile_MOTHER
{
public:
	Foreground(int ID, int x_pos, int y_pos, TileMap &TM);
	//Directions, 0 = up, 1 = right, 2 = down, 3 = left.
	static void Addline(unsigned int ID, int x, int y, int direction, int distance, TileMap &TM);
};

