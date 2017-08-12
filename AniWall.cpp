#include "stdafx.h"
#include "AniWall.h"


AniWall::AniWall(int ID, int x_pos, int y_pos, TileMap &TM)
{
	typeID = 19;
	spriteID = ID;
	x = x_pos;
	y = y_pos;

	Sprites = All_Sprites[TM.getTextureID()][typeID][ID];
	//This decides the booleans that come with the sprites.
	switch (TM.getTextureID()) {
	case 3:
		switch (ID) {
		case 0:
			max_ticks = 0.2;
			break;
		case 1:
			max_ticks = 0.09;
		}
		break;
	}
	switch (ID) {
	case 0:
		isSIMPLELIGHTING = true;
		break;
	}
	GF::CheckTile_OverLap(x, y);
	sprite.setup();
	sprite.setPosition(x, y);
	sprite *= Sprites[0];
	SavedParameters = { x_pos, y_pos, ID };
	ColAniTiles.push_back(this);
}


void AniWall::Addline(unsigned int ID, int x, int y, int direction, int distance, TileMap &TM) {
	//Checking the direction that the line extends in.
	switch (direction) {
		//In the case the user wants it in the direction up.
	case 0:
		for (int i = 0; i <= distance; i++) {
			new AniWall(ID, x, y + ((i*-1)*base32), TM);
		};
		break;
		//In the case the user wants it in the direction right.
	case 1:
		for (int i = 0; i <= distance; i++) {
			new AniWall(ID, x + ((i)*base32), y, TM);
		};
		break;
		//In the case the user wants it in the direction down.
	case 2:
		for (int i = 0; i <= distance; i++) {
			new AniWall(ID, x, y + ((i)*base32), TM);
		};
		break;
		//In the case the user wants it in the direction left.
	case 3:
		for (int i = 0; i <= distance; i++) {
			new AniWall(ID, x + ((i*-1)*base32), y, TM);
		};
		break;
	}


}
