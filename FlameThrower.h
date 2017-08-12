#pragma once
#include "Basic_Tile_MOTHER.h"
//Item name: FlameThrower
//Date made 12/15/2016 11:31:45 PM
//Made by Josh

class FlameThrower : public Basic_Tile_MOTHER
{
private:
	//This is a pointer to the tilemap, it is held here so that it can be used in the animate function when creating a flame.
	TileMap *Tmap;
	//This is the direction that it shoots the flame.
	int direction = 0;
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
	//This overwrites the animation function.
	void animate();
public:
	/*This is a tile that, surprisingly, throws flames.*/
	FlameThrower(int type, int x_pos, int y_pos, int Direction, TileMap &TM);

};

