#pragma once
#include "Basic_Tile_MOTHER.h"
#include "PText.h"
#include "TempText.h"
///This tile replenishes the fuel that the player has.
///Stepping on this will make the fuel go up.

class RTile : public Basic_Tile_MOTHER
{
private:
	
	//This tells the tile whether or not the tile has been stood on by the player.
	bool hasBeenLandedOn = false;
	//This tells how much fuel the tile should replenish in the player.
	int amount = 0;
	//This is the type of RTile it is.
	int Type = 0;
	//This contains the sprites that are needed to function properly.
	std::vector<std::vector<AniT>> spr;
public:
	RTile(const int &type, const int &x_pos, const int &y_pos, TileMap &TM);
	//This tells the computer what to do if the player has landed on the tile.
	bool ifCollision(int PlayerChannel);
};

