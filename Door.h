#pragma once
#include "Basic_Tile_MOTHER.h"
class Door: public Basic_Tile_MOTHER
{
private:
	int Type = 0;
	bool isOpen = false;
	int E = -1;
	int Exit_X = 0;
	int Exit_Y = 0;
	int Direction = -1;
	bool isChecking = false;
public:
	Door(int x_pos, int y_pos, int exit_X, int exit_Y, int Extra, int direction, int type, TileMap &TM);
	bool ifCollisionBefore(bool isPlayer);
	bool elseCollisionBefore(int PlayerChannel);
};

