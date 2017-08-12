#pragma once
#include "Basic_Tile_MOTHER.h"
class Rock : public Basic_Tile_MOTHER
{
private:
	//This is the type of rock that it is.
	int type = 0;
	//This is the particles settings that tell what the particles do whenever you hit the rock.
	ParticleSettings settings;
public:
	Rock(int Type, int x_pos, int y_pos, TileMap &TM);
	bool ifCollisionBefore(bool isPlayer);
};

