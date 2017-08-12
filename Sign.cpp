#include "stdafx.h"
#include "Sign.h"
#include "Light_MOTHER.h"
#include "Dia.h"
#include "GF.h"
#include <iostream>
#include "Player.h"
Sign::Sign(int type, int x_pos, int y_pos, TileMap &TM)
{
	typeID = 15;
	spr = All_Sprites[TM.getTextureID()][15][0];
	sprite *= spr[0];
	sprite.setPosition(x_pos, y_pos);
	//sprite.setTexture(TM.getTextureID());
	sprite.setup();
	//Gettng the sprite out.
	Type = type;
	x = x_pos;
	y = y_pos;
	GF::CheckTile_OverLap(x, y);
	SavedParameters = { x_pos, y_pos, type };
	//Putting the object that was just created into a static vector to be used later.
	ColTiles.push_back(this);
}


void Sign::tick() {

}


bool Sign::CheckCollision_Over(int Your_xpos, int Your_ypos) {
	if (Player::PlayerObjects[0]->getx() < x) {
		sprite *= spr[1];
	}
	else if (Player::PlayerObjects[0]->getx() > x) {
		sprite *= spr[2];
	}
	else if(Player::PlayerObjects[0]->getx() == x){
		sprite *= spr[0];
	}
	//This checks to see if your pixels line up with the wall object's pixels.
	if ((Your_xpos == x) && (Your_ypos == y)) {
		if (Willing_to_inform == true) {
			if (Dia::getcachelength() != 0) {
				Dia(Dia::getDia_sprite(2), "Good heavens! How rude you are! You musn't ignore people.");
				Dia(Dia::getDia_sprite(2), "I am not giving you any information until you listen.");
				Willing_to_inform = false;
			}
			else{
				switch (Type) {
				case 0:
					
					switch (Player::PlayerObjects[0]->get_difficulty()) {
					case 0:
						Dia(Dia::getDia_sprite(3), Dia::getDia_string(4));
						Dia(Dia::getDia_sprite(3), Dia::getDia_string(5));
						Dia(Dia::getDia_sprite(3), Dia::getDia_string(21));
						Dia(Dia::getDia_sprite(3), Dia::getDia_string(22));
						Dia(Dia::getDia_sprite(3), Dia::getDia_string(7));
						break;
					case 1:
						Dia(Dia::getDia_sprite(3), Dia::getDia_string(4));
						Dia(Dia::getDia_sprite(3), Dia::getDia_string(5));
						Dia(Dia::getDia_sprite(3), Dia::getDia_string(21));
						Dia(Dia::getDia_sprite(3), Dia::getDia_string(22));
						Dia(Dia::getDia_sprite(3), Dia::getDia_string(7));
						break;
					case 2: //Only if it is on hard will he explain the lasers.
						//No need to explain lasers that aren't there.
						Dia(Dia::getDia_sprite(3), Dia::getDia_string(4));
						Dia(Dia::getDia_sprite(3), Dia::getDia_string(5));
						Dia(Dia::getDia_sprite(3), Dia::getDia_string(6));
						Dia(Dia::getDia_sprite(3), Dia::getDia_string(22));
						Dia(Dia::getDia_sprite(3), Dia::getDia_string(7));
						break;
					
					}
					
					break;
				case 1:
					Dia(Dia::getDia_sprite(3), Dia::getDia_string(8));
					break;
				case 2:
					Dia(Dia::getDia_sprite(3), Dia::getDia_string(9));
					Dia(Dia::getDia_sprite(1), Dia::getDia_string(10));
					break;
				case 3:
					Dia(Dia::getDia_sprite(1), Dia::getDia_string(11));
					Dia(Dia::getDia_sprite(3), Dia::getDia_string(12));
					Dia(Dia::getDia_sprite(3), Dia::getDia_string(13));
					Dia(Dia::getDia_sprite(3), Dia::getDia_string(14));
					Dia(Dia::getDia_sprite(3), Dia::getDia_string(15));
					Dia(Dia::getDia_sprite(3), Dia::getDia_string(16));
					Dia(Dia::getDia_sprite(3), Dia::getDia_string(17));
					Dia(Dia::getDia_sprite(1), Dia::getDia_string(18));
					Dia(Dia::getDia_sprite(3), Dia::getDia_string(19));
					Dia(Dia::getDia_sprite(2), Dia::getDia_string(20));
					break;
				case 4:
					Dia(Dia::getDia_sprite(3), Dia::getDia_string(23));
					break;
				}
				Willing_to_inform = false;
			}
		}
		else {
			if (Dia::getcachelength() == 0) {
				Willing_to_inform = true;
			}
		}
		
		return true;
	}
	//This happens if it did not line up.
	else {
		return false;
	}
}
