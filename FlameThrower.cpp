#include "stdafx.h"
#include "FlameThrower.h"
#include "Projectile.h"
#include "TileMap.h"
#include "Flame.h"

FlameThrower::FlameThrower(int type, int x_pos, int y_pos, int Direction, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	Tmap = &TM;
	typeID = 22; //This identifies this kind of derived object as a something different than the rest of them.
	max_ticks = 2; //Normal 0.1 ~how long is takes to get to the next frame of the animation.
	sprite.setTexture(0); //This tells the computer when to draw the sprite. Background, Character, or Foreground.
	sprite.setPosition(x, y); //This is for setting the position of the sprite to the x and y coordinates.
	sprite.setup(); //This is telling the computer that the sprite is ready to be drawn.
	isSIMPLELIGHTING = false; //If this is set to true, it will always be as bright as possible; Otherwise, it will lit by the surrounding light.
	SavedParameters = {type, x_pos, y_pos, Direction}; //These are the parameters that are saved when loading the tile.
	Sprites = All_Sprites[TM.getTextureID()][typeID][0];
	direction = Direction;
	sprite *= Sprites[Direction];

	ColAniTiles.push_back(this);
}



///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-~VIRTUAL FUNCTIONS~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
///These are functions are overwritten virtual functions of the mother class Basic_Tile_MOTHER.
///Write in these if you want something to happen depending on the function;
///Otherwise, you can leave them empty, and nothing will happen.
///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


//This tells the computer what to do if the player stepped on the tile.
bool FlameThrower::ifCollision(int PlayerChannel) {
	return false;
}

//This tells the computer what to do if the player collides with the tile before he/she lands on it.
bool FlameThrower::ifCollisionBefore(bool isPlayer) {
	return true;
}

//This tells the computer what to do if the player is not colliding with the tile.
bool FlameThrower::elseCollisionBefore(int PlayerChannel) {
	return true;
}

//This tells the computer what to do if a projectile is colliding with the tile.
//Will return false if not no collision occured.
//Will return true if a collision occured.
void FlameThrower::ifProjectileCollision(Projectile &P, int direction) {

}

void FlameThrower::animate() {
	ticks += GF::getDelta();
	if (ticks >= max_ticks) {
		new Flame(0, x, y, direction, *Tmap);
		ticks -= max_ticks;
	}
}