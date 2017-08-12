#include "stdafx.h"
#include "AniBg.h"
#include "Light_MOTHER.h"
#include <iostream>
#include <memory>
AniBg::AniBg(int ID, int x_pos, int y_pos, TileMap &TM)
{
	
	typeID = 4;
	spriteID = ID;
	x = x_pos;
	y = y_pos;
	
	Sprites = All_Sprites[TM.getTextureID()][typeID][ID];
	//This decides the booleans that come with the sprites.
	switch (TM.getTextureID()) {
	case 1:
		switch (ID) {
		case 3:
			max_ticks = 0.2;
			break;
		
		default:
			max_ticks = 0.2;
		}
		break;
	case 6:
		switch (ID) {
		
		case 6:
			
			isSIMPLELIGHTING = true;
			
			//throw("erroz");
			max_ticks = 0.02;
			sprite.setTexture(2);
			break;
		case 7:
			
			isSIMPLELIGHTING = true;
			
			//throw("erroz");
			max_ticks = 0.02;
			sprite.setTexture(2);
			break;
		}
	case 7:
		switch (ID) {
		case 8:
			isSIMPLELIGHTING = true;
			max_ticks = 0.02;
			break;
		case 9:
			isSIMPLELIGHTING = true;
			max_ticks = 0.02;
			break;
		case 10:
			isSIMPLELIGHTING = true;
			max_ticks = 0.02;
			break;
		}
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
	NonColAniTiles_FORE.push_back(this);
}


void AniBg::Addline(unsigned int ID, int x, int y, int direction, int distance, TileMap &TM) {
	//Checking the direction that the line extends in.
	switch (direction) {
		//In the case the user wants it in the direction up.
	case 0:
		for (int i = 0; i <= distance; i++) {
			new AniBg(ID, x, y + ((i*-1)*base32), TM);
		};
		break;
		//In the case the user wants it in the direction right.
	case 1:
		for (int i = 0; i <= distance; i++) {
			new AniBg(ID, x + ((i)*base32), y, TM);
		};
		break;
		//In the case the user wants it in the direction down.
	case 2:
		for (int i = 0; i <= distance; i++) {
			new AniBg(ID, x, y + ((i)*base32), TM);
		};
		break;
		//In the case the user wants it in the direction left.
	case 3:
		for (int i = 0; i <= distance; i++) {
			new AniBg(ID, x + ((i*-1)*base32), y, TM);
		};
		break;
	}


}
