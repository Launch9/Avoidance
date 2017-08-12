#include "stdafx.h"
#include "PTile.h"
#include "Light_MOTHER.h"
#include "Player.h"
#include "P_Switch_MAIN.h"
#include "Seal.h"
#include "Sound.h"
#include "random2.h"

std::vector<PTile *> PTile::Objects;

PTile::PTile(int type, int x_pos, int y_pos, int SwitchChannel, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	GF::CheckTile_OverLap(x_pos, y_pos);
	SC = SwitchChannel;
	typeID = 14;
	sprite.setPosition(x, y);
	switch (type) {
	case 0: //Once stepped on, active untill new world loaded.
		spr = All_Sprites[TM.getTextureID()][typeID][0];
		Sprites = { All_Sprites[TM.getTextureID()][typeID][0][0], All_Sprites[TM.getTextureID()][typeID][0][1] };
		//Only if standing on will be active.
		//Otherwise it will be off.
		lambda_geton = [&](PTile *P) {
			if (P->has_landed == false && P->is_on == true) {
				Sound::Play(18, x, y, random2::randomrange(1, 5), 0, 0);
				P->turn_off();
				P_Switch_MAIN::Switches[P->SC] = true;
				P->has_landed = true;
			}
		};
		lambda_getoff = [&](PTile *P) {
		};
		break;
	case 1: //Only active if currently standing on; Otherwise, inactive.
		spr = All_Sprites[TM.getTextureID()][typeID][0];
		Sprites = { All_Sprites[TM.getTextureID()][typeID][0][0],All_Sprites[TM.getTextureID()][typeID][0][1] };
		lambda_geton = [&](PTile *P) {
			Sound::Play(18, x, y, random2::randomrange(1, 5), 0, 0);
			P->turn_off();
			P_Switch_MAIN::Switches[P->SC] = true;
		};
		lambda_getoff = [&](PTile *P) {
			P->turn_on();
			P_Switch_MAIN::Switches[P->SC] = false;
		};
		break;
	case 2: //Only active for one frame upon stepping on it.
		spr = All_Sprites[TM.getTextureID()][typeID][0];
		Sprites = { All_Sprites[TM.getTextureID()][typeID][0][0], All_Sprites[TM.getTextureID()][typeID][0][1] };
		lambda_geton = [&](PTile *P) {
			
			if (isSteppingon == false) {
				
				Sound::Play(18, x, y, random2::randomrange(1,5), 0, 0);
				P->turn_off();
				P_Switch_MAIN::Switches[P->SC] = true;
				isSteppingon = true;
			}
			else {
				
				P->turn_on();
				P_Switch_MAIN::Switches[P->SC] = false;
			}
		};
		lambda_getoff = [&](PTile *P) {
			
			P->turn_on();
			P_Switch_MAIN::Switches[P->SC] = false;
			isSteppingon = false;
		};
	}
	sprite.setup();
	Light_MOTHER::SetColorAndLighting(color, x, y);
	sprite.setColor(color);
	sprite *= Sprites[0];
	SavedParameters = { x_pos, y_pos, type, SwitchChannel };
	NonColAniTiles.push_back(this);
	Objects.push_back(this);
	
}

PTile::~PTile() {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		if (Objects[i] == this) {
			Objects.erase(Objects.begin() + i);
		}
	}
}
bool PTile::elseCollisionBefore(int PlayerChannel) {
	return false;
}

void PTile::animate() {
	ticks += GF::getDelta();
	if (ticks >= max_ticks) {
		svectorindex += 1;
		if (svectorindex >= Sprites.size()) {
			svectorindex = 0;
			//Setting the texture rectangle to the correct position for proper animation.
		}
		sprite *= Sprites[svectorindex];
		ticks -= max_ticks;
	}
	if (x == Player::PlayerObjects[0]->getx() && y == Player::PlayerObjects[0]->gety()) {
		lambda_geton(this); //Stepping on the switch
		P_Switch_MAIN::update();
	}
	else {
		
		if (isSteppingon == true) {
			
			isSteppingon = false;
			lambda_getoff(this);
		}
		P_Switch_MAIN::update();
	}
	
}

bool PTile::ifCollision(int PlayerChannel) {
	return false;
}


void PTile::turn_off() {
	if (is_on == true) {
		is_on = false;
		changeAni({ spr[2] });
	}
	
}

void PTile::turn_on() {
	if (is_on == false) {
		is_on = true;
		changeAni({ spr[0],spr[1] });
	}
	
}

void PTile::update() {
	if (P_Switch_MAIN::Switches[SC] == false) {
		has_landed = false;
		turn_on();
	}
	else {
		has_landed = true;
		turn_off();
	}
}
void PTile::update_all() {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		Objects[i]->update();
	}
}