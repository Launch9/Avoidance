#include "stdafx.h"
#include "P_Spawner_Const.h"
#include <iostream>
#include "P_Switch_MAIN.h"
P_Spawner_Const::P_Spawner_Const(const int &type, const int &x_pos, const int &y_pos, const int &Direction, TileMap &TM, const int &SwitchChannel)
{
	x = x_pos;
	y = y_pos;
	typeID = 13;
	switch (type) {
	case 0: //standard: zero particles
		type_of_projectile = 2;
		max_ticks_til_shot = 1;
		break;
	case 1: //slow: zero particles
		type_of_projectile = 1;
		max_ticks_til_shot = 3;
		break;
	}
	channel = SwitchChannel;
	dir = Direction;
	max_ticks = 0.2;
	sprite.setPosition(x, y);
	sprite.setup();
	isSIMPLELIGHTING = false;
	SavedParameters = { x_pos, y_pos, type, dir, channel };
	switch (Direction) {
	case 0:
		Sprites = { All_Sprites[TM.getTextureID()][typeID][0][0], All_Sprites[TM.getTextureID()][typeID][0][1] };
		break;
	case 1:
		Sprites = { All_Sprites[TM.getTextureID()][typeID][0][2], All_Sprites[TM.getTextureID()][typeID][0][3] };
		break;
	case 2:
		Sprites = { All_Sprites[TM.getTextureID()][typeID][0][4], All_Sprites[TM.getTextureID()][typeID][0][5] };
		break;
	case 3:
		Sprites = { All_Sprites[TM.getTextureID()][typeID][0][6], All_Sprites[TM.getTextureID()][typeID][0][7] };
		break;
	}
	sprite *= Sprites[0];
	ColAniTiles.push_back(this);
}

int P_Spawner_Const::getType_of_projectile() {
	return type_of_projectile;
}

void P_Spawner_Const::animate() {
	if (channel == -1) {
		real_animate();
	}
	else {
		if (P_Switch_MAIN::Switches[channel] == true) {
			real_animate();
		}
	}
}

void P_Spawner_Const::real_animate() {
	ticks += GF::getDelta();
	Fcounter += GF::getDelta();
	if (ticks >= max_ticks) {
		if (svectorindex < Sprites.size()) {
			//Setting the texture rectangle to the correct position for proper animation.
			sprite *= Sprites[svectorindex];
			svectorindex += 1;

		}
		else {
			svectorindex = 0;
		}
		ticks = 0;
	}
	if (Fcounter >= max_ticks_til_shot) {

		Fcounter = 0;
		switch (dir) {
		case 0:
			Projectile(type_of_projectile, x, y, dir);
			break;
		case 1:
			Projectile(type_of_projectile, x + 32, y, dir);
			break;
		case 2:
			Projectile(type_of_projectile, x, y + 32, dir);
			break;
		case 3:
			Projectile(type_of_projectile, x, y, dir);
			break;
		}


	}

}