#include "stdafx.h"
#include "Bg.h"
#include "Light_MOTHER.h"
#include <memory>
#define base32 32





Bg::Bg(int ID, int x_pos, int y_pos, TileMap &TM) {
	
	
	typeID = 1;
	sprite *= All_Sprites[TM.getTextureID()][typeID][0][ID];
	sprite.setTexture(0);
	sprite.setup();
	x = x_pos;
	y = y_pos;
	GF::CheckTile_OverLap(x, y);
	sprite.setPosition(x, y);
	Light_MOTHER::SetColorAndLighting(color, x, y);
	SavedParameters = { x_pos, y_pos, ID };
	sprite.setColor(color);
	NonColTiles.push_back(this);
}





void Bg::Addline(unsigned int ID, int x, int y, int direction, int distance, TileMap &TM) {
	//Checking the direction that the line extends in.
	switch (direction) {
		//In the case the user wants it in the direction up.
	case 0:
		for (int i = 0; i <= distance; i++) {
			new Bg(ID, x, y + ((i*-1)*base32), TM);
		};
		break;
		//In the case the user wants it in the direction right.
	case 1:
		for (int i = 0; i <= distance; i++) {
			new Bg(ID, x + ((i)*base32), y, TM);
		};
		break;
		//In the case the user wants it in the direction down.
	case 2:
		for (int i = 0; i <= distance; i++) {
			new Bg(ID, x, y + ((i)*base32), TM);
		};
		break;
		//In the case the user wants it in the direction left.
	case 3:
		for (int i = 0; i <= distance; i++) {
			new Bg(ID, x + ((i*-1)*base32), y, TM);
		};
		break;
	}

	
}


