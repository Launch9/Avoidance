#include "stdafx.h"
#include "Corner.h"
#include <iostream>
#include "Sound.h"
#include "ParticleSettings.h"
#include "ParticleSystem.h"
#include "random2.h"
Corner::Corner(const int &type, const int &x_pos, const int &y_pos, const int &Direction, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	typeID = 9;
	dir = Direction;
	sprite.setPosition(x, y);
	sprite.setup();
	isSIMPLELIGHTING = true;
	SavedParameters = { x_pos, y_pos, type, dir };
	switch (Direction) {
	case 0:
		Sprites = { All_Sprites[TM.getTextureID()][typeID][0][0], All_Sprites[TM.getTextureID()][typeID][0][4] };
		break;
	case 1:
		Sprites = { All_Sprites[TM.getTextureID()][typeID][0][1], All_Sprites[TM.getTextureID()][typeID][0][5] };
		break;
	case 2:
		Sprites = { All_Sprites[TM.getTextureID()][typeID][0][2], All_Sprites[TM.getTextureID()][typeID][0][6] };
		break;
	case 3:
		Sprites = { All_Sprites[TM.getTextureID()][typeID][0][3], All_Sprites[TM.getTextureID()][typeID][0][7] };
		break;
	}
	sprite *= Sprites[0]; //Making sure there is a sprite there to draw before the animation kicks in.
	ColProjectiles.push_back(this);
}

void Corner::ifProjectileCollision(Projectile &P, int direction) {
	
	switch (dir) {
	case 0: //Top left
		switch (direction) {
		case 2: //Coming in down
			P.changedirection(3, true, true);
			break;
		case 1: //Coming in right
			P.changedirection(0, true, true);
			break;
		}
		break;
	case 1: //Top right
		switch (direction) {
		case 2: //Coming in down
			P.changedirection(1, true, true);
			break;
		case 3: //Coming in left
			P.changedirection(0, true, true);
			break;
		}
		break;
	case 2: //Bottom right
		switch (direction) {
		case 3: //Coming in left
			P.changedirection(2, true, true);
			break;
		case 0: //Coming in up
			P.changedirection(1, true, true);
			break;
		}
		break;
	case 3: //Bottom left
		switch (direction) {
		case 1: //Coming in right
			P.changedirection(2, true, true);
			break;
		case 0: //Coming in up
			P.changedirection(3, true, true);
			break;
		}
	}

	
	
	
	Sound::Play(19, x, y, random2::randomrange(1, 5), 0, 0);
}

