#pragma once
#include "Basic_Tile_MOTHER.h"
//Item name: BounceTile
//Date made 11/15/2016 12:58:45 AM
//Made by Josh

class BounceTile : public Basic_Tile_MOTHER
{
private:
	//This is the direction that the tile bounces you in.
	int direction = 0;
	//This is the type of bouncetile that it is.
	int type = 0;
	//This tells the computer what to do if the player stepped on the tile.
	bool ifCollision(int PlayerChannel);
	//This tells the computer what to do if the player collides with the tile before he/she lands on it.
	bool ifCollisionBefore(bool isPlayer);
	//This tells the computer what to do if the player is not colliding with the tile.
	bool elseCollisionBefore(int PlayerChannel);
	//This is the distance that it sends you in blocks.
	int distance = 0;
	//This tells the computer what to do if a projectile is colliding with the tile.
	//Will return false if not no collision occured.
	//Will return true if a collision occured.
	void ifProjectileCollision(Projectile &P, int direction);
public:
	/*This is a tile that bounces the player in the direction given. It will bounce the player the distance(in tiles) given.*/
	BounceTile(int type, int Distance, int x_pos, int y_pos, int direction, TileMap &TM);

};

