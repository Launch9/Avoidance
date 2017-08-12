#include "stdafx.h"
#include "EyeBall.h"
#include "Projectile.h"
#include "TileMap.h"
#include "Projectile.h"
#include "P_Switch_MAIN.h"
#include "EBM.h"
#include "Sound.h"
#include "random2.h"
EyeBall::EyeBall(int type, int x_pos, int y_pos, int Direction, int Switch, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	Tmap = &TM;
	Switch_I = Switch;
	direction = Direction;
	typeID = 21; //This identifies this kind of derived object as a something different than the rest of them.
	max_ticks = 0.1; //Normal 0.1 ~how long is takes to get to the next frame of the animation.
	sprite.setTexture(0); //This tells the computer when to draw the sprite. Background, Character, or Foreground.
	sprite.setPosition(x, y); //This is for setting the position of the sprite to the x and y coordinates.
	sprite.setup(); //This is telling the computer that the sprite is ready to be drawn.
	isSIMPLELIGHTING = false; //If this is set to true, it will always be as bright as possible; Otherwise, it will lit by the surrounding light.
	SavedParameters = {type, x_pos, y_pos, Direction, Switch }; //These are the parameters that are saved when loading the tile.
	sprites = All_Sprites[TM.getTextureID()][typeID];
	sprite *= sprites[0][direction];

	ColProjectiles.push_back(this);
}



///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-~VIRTUAL FUNCTIONS~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
///These are functions are overwritten virtual functions of the mother class Basic_Tile_MOTHER.
///Write in these if you want something to happen depending on the function;
///Otherwise, you can leave them empty, and nothing will happen.
///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


//This tells the computer what to do if the player stepped on the tile.
bool EyeBall::ifCollision(int PlayerChannel) {
	return false;
}

//This tells the computer what to do if the player collides with the tile before he/she lands on it.
bool EyeBall::ifCollisionBefore(bool isPlayer) {
	return true;
}

//This tells the computer what to do if the player is not colliding with the tile.
bool EyeBall::elseCollisionBefore(int PlayerChannel) {
	return true;
}

void EyeBall::animate() {

}
//This tells the computer what to do if a projectile is colliding with the tile.
//Will return false if not no collision occured.
//Will return true if a collision occured.
void EyeBall::ifProjectileCollision(Projectile &P, int direction) {
	P.kill(1);
	if (isOpen == true) {
		close();
	}
}


void EyeBall::close() {
	isOpen = false;
	switch (direction) {
	case 0:
		new EBM(0, x - 32, y - 32, *Tmap);
		new EBM(0, x + 32, y - 32, *Tmap);
		break;
	case 1:
		new EBM(0, x + 32, y - 32, *Tmap);
		new EBM(0, x + 32, y + 32, *Tmap);
		break;
	case 2:
		new EBM(0, x - 32, y + 32, *Tmap);
		new EBM(0, x + 32, y + 32, *Tmap);
		break;
	case 3:
		new EBM(0, x - 32, y - 32, *Tmap);
		new EBM(0, x - 32, y + 32, *Tmap);
	}
	Sound::Play(52, 0, 0, random2::randomrange(1, 6));
	sprite *= sprites[1][direction];
	P_Switch_MAIN::Switches[Switch_I] = true;
}
//This opens the eyeball.
void EyeBall::open() {
	isOpen = true;
	sprite *= sprites[1][direction];
	P_Switch_MAIN::Switches[Switch_I] = false;
}