#include "stdafx.h"
#include "Foreground.h"
#include "Light_MOTHER.h"
#include <iostream>
#include <memory>
#define base32 32
Foreground::Foreground(int ID, int x_pos, int y_pos, TileMap &TM)
{
	
	typeID = 7;
	sprite *= All_Sprites[TM.getTextureID()][typeID][0][ID];
	/*switch (ID) {
	case 0:
		isSIMPLELIGHTING = true;
		//sprite.rotate(90);
		break;
	case 1:
		isSIMPLELIGHTING = true;
		//sprite.rotate(180);
		break;
	case 2:
		isSIMPLELIGHTING = true;
		//sprite.rotate(270);
		break;
	case 3:
		isSIMPLELIGHTING = true;
		break;
	}*/
	x = x_pos;
	y = y_pos;
	GF::CheckTile_OverLap(x, y);
	SavedParameters = { x_pos, y_pos, ID };
	sprite.setPosition(x, y);
	sprite.setTexture(2);
	sprite.setup();
	Light_MOTHER::SetColorAndLighting(color, x, y);
	
	//sprite.setColor(color);
	NonColTiles_FORE.push_back(this);
	
}

void Foreground::Addline(unsigned int ID, int x, int y, int direction, int distance, TileMap &TM) {
	//Checking the direction that the line extends in.
	switch (direction) {
		//In the case the user wants it in the direction up.
	case 0:
		for (int i = 0; i <= distance; i++) {
			new Foreground(ID, x, y + ((i*-1)*base32), TM);
		};
		break;
		//In the case the user wants it in the direction right.
	case 1:
		for (int i = 0; i <= distance; i++) {
			new Foreground(ID, x + ((i)*base32), y, TM);
		};
		break;
		//In the case the user wants it in the direction down.
	case 2:
		for (int i = 0; i <= distance; i++) {
			new Foreground(ID, x, y + ((i)*base32), TM);
		};
		break;
		//In the case the user wants it in the direction left.
	case 3:
		for (int i = 0; i <= distance; i++) {
			new Foreground(ID, x + ((i*-1)*base32), y, TM);
		};
		break;
	}


}

