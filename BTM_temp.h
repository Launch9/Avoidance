#pragma once
#include "Basic_Tile_MOTHER.h"


class BTM_temp : public Basic_Tile_MOTHER
{
private:
	//This tells the computer what to do if the player stepped on the tile.
	bool ifCollision(int PlayerChannel);
	//This tells the computer what to do if the player collides with the tile before he/she lands on it.
	bool ifCollisionBefore(bool isPlayer);
	//This tells the computer what to do if the player is not colliding with the tile.
	bool elseCollisionBefore(int PlayerChannel);
	//This tells the computer what to do if a projectile is colliding with the tile.
	//Will return false if not no collision occured.
	//Will return true if a collision occured.
	void ifProjectileCollision(Projectile &P, int direction);
public:
	/*Put description here.*/
	BTM_temp(int type, int x_pos, int y_pos, TileMap &TM);

};

