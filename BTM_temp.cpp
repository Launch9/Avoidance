#include "stdafx.h"
#include "BTM_temp.h"
#include "Projectile.h"
#include "TileMap.h"

BTM_temp::BTM_temp(int type, int x_pos, int y_pos, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
//	typeID = ; //This identifies this kind of derived object as a something different than the rest of them.
//	max_ticks = ; //Normal 0.1 ~how long is takes to get to the next frame of the animation.
	sprite.setTexture(0); //This tells the computer when to draw the sprite. Background, Character, or Foreground.
	sprite.setPosition(x, y); //This is for setting the position of the sprite to the x and y coordinates.
	sprite.setup(); //This is telling the computer that the sprite is ready to be drawn.
	isSIMPLELIGHTING = false; //If this is set to true, it will always be as bright as possible; Otherwise, it will lit by the surrounding light.
	SavedParameters = {type, x_pos, y_pos}; //These are the parameters that are saved when loading the tile.
//	Sprites = All_Sprites[TM.getTextureID()][typeID][];
	sprite *= Sprites[0];

//	/*type of object vector here*/.push_back(this);
}



///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-~VIRTUAL FUNCTIONS~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
///These are functions are overwritten virtual functions of the mother class Basic_Tile_MOTHER.
///Write in these if you want something to happen depending on the function;
///Otherwise, you can leave them empty, and nothing will happen.
///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


//This tells the computer what to do if the player stepped on the tile.
bool BTM_temp::ifCollision(int PlayerChannel) {
	return false;
}

//This tells the computer what to do if the player collides with the tile before he/she lands on it.
bool BTM_temp::ifCollisionBefore(bool isPlayer) {
	return true;
}

//This tells the computer what to do if the player is not colliding with the tile.
bool BTM_temp::elseCollisionBefore(int PlayerChannel) {
	return true;
}

//This tells the computer what to do if a projectile is colliding with the tile.
//Will return false if not no collision occured.
//Will return true if a collision occured.
void BTM_temp::ifProjectileCollision(Projectile &P, int direction) {

}