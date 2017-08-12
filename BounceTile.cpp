#include "stdafx.h"
#include "BounceTile.h"
#include "Projectile.h"
#include "TileMap.h"
#include <iostream>
#include "Player.h"
#include "Sound.h"
#include "random2.h"
BounceTile::BounceTile(int Type, int Distance, int x_pos, int y_pos, int Direction, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	direction = Direction;
	type = Type;
	distance = Distance;
	typeID = 20; //This identifies this kind of derived object as a something different than the rest of them.
	max_ticks = 0; //Normal 0.1 ~how long is takes to get to the next frame of the animation.
	sprite.setTexture(0); //This tells the computer when to draw the sprite. Background, Character, or Foreground.
	sprite.setPosition(x, y); //This is for setting the position of the sprite to the x and y coordinates.
	sprite.setup(); //This is telling the computer that the sprite is ready to be drawn.
	isSIMPLELIGHTING = false; //If this is set to true, it will always be as bright as possible; Otherwise, it will lit by the surrounding light.
	SavedParameters = {type, distance, x_pos, y_pos, Direction}; //These are the parameters that are saved when loading the tile.
	sprite *= All_Sprites[TM.getTextureID()][typeID][0][direction];

	NonColTiles.push_back(this);
}



///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-~VIRTUAL FUNCTIONS~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
///These are functions are overwritten virtual functions of the mother class Basic_Tile_MOTHER.
///Write in these if you want something to happen depending on the function;
///Otherwise, you can leave them empty, and nothing will happen.
///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


//This tells the computer what to do if the player stepped on the tile.
bool BounceTile::ifCollision(int PlayerChannel) {
	
	Sound::Play(44, 0, 0, random2::randomrange(1, 5));
	switch (direction) {
	case 0:
		Player::PlayerObjects[0]->bounceup(distance * 32);
		break;
	case 1:
		Player::PlayerObjects[0]->bounceright(distance * 32);
		break;
	case 2:
		Player::PlayerObjects[0]->bouncedown(distance * 32);
		break;
	case 3:
		Player::PlayerObjects[0]->bounceleft(distance * 32);
		break;
	}
	return false;
}

//This tells the computer what to do if the player collides with the tile before he/she lands on it.
bool BounceTile::ifCollisionBefore(bool isPlayer) {
	return true;
}

//This tells the computer what to do if the player is not colliding with the tile.
bool BounceTile::elseCollisionBefore(int PlayerChannel) {
	return true;
}

//This tells the computer what to do if a projectile is colliding with the tile.
//Will return false if not no collision occured.
//Will return true if a collision occured.
void BounceTile::ifProjectileCollision(Projectile &P, int direction) {

}

