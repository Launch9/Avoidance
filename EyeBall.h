#pragma once
#include "Basic_Tile_MOTHER.h"
//Item name: EyeBall
//Date made 12/3/2016 5:09:35 PM
//Made by Josh

class EyeBall : public Basic_Tile_MOTHER
{
private:
	//Overwritting the animation function.
	void animate();
	//This is the switch that activates when the eyeball is shot.
	int Switch_I = 0;
	//This contains all the sprites the eyeball is going to use.
	std::vector<std::vector<AniT>> sprites;
	//This tells if the eyeball is closed or open.
	bool isOpen = true;
	//This is a pointer to the Tilemap.
	TileMap *Tmap;
	//This is the direction that the eyeball is in.
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
	//This closes the eyeball.
	void close();
	//This opens the eyeball.
	void open();
public:
	/*Put description here.*/
	EyeBall(int type, int x_pos, int y_pos, int Direction, int Switch, TileMap &TM);

};

