#pragma once
#include "Basic_Tile_MOTHER.h"
class Corner: public Basic_Tile_MOTHER

{
private:
	int dir = 0;
	//Happens if collision with something important.
	void ifProjectileCollision(Projectile &P, int direction);
public:
	Corner(const int &type, const int &x_pos, const int &y_pos, const int &Direction, TileMap &TM);

	
};

