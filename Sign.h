#pragma once
#include "Basic_Tile_MOTHER.h"

class Sign : public Basic_Tile_MOTHER
{
private:
	std::vector<AniT> spr; //AniTs to be used during gameplay.
	bool Willing_to_inform = true;
	int Type = 0;
	std::string String = "";
public:
	Sign(int type, int x_pos, int y_pos, TileMap &TM);
	bool CheckCollision_Over(int Your_xpos, int Your_ypos);
	void tick();
};

