#include "stdafx.h"
#include "Chest.h"
#include "Light_MOTHER.h"
#include "Player.h"
#include "Temporarytxt.h"
#include "GF.h"
#include "Font.h"
#include "Itemids.h"
#include "GUI.h"
#include <memory>
#include "TempText.h"
#include "Sound.h"
#include "P_Switch_MAIN.h"
#include "random2.h"
std::vector<Chest *> Chest::Chests;
Chest::Chest(int ID, int x_pos, int y_pos, int contentID, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	typeID = 8;
	spriteID = ID;
	
	switch (ID) {
	case 0:
		spr = All_Sprites[TM.getTextureID()][typeID][0];
		Switch = -1;
		break;
	case 1:
		spr = All_Sprites[TM.getTextureID()][typeID][0];
		Switch = 0;
		sprite.deactivate();
		break;
	case 2: //Chest at end of dungeon
		spr = All_Sprites[TM.getTextureID()][typeID][1];
		Switch = 0;
		sprite.deactivate();
		break;
	}
	sprite.setup();
	sprite.setPosition(x, y);
	particle_settings.x = x + 16;
	particle_settings.y = y + 16;
	particle_settings.color = sf::Color::White;
	particle_settings.max_speed = 2;
	particle_settings.num_of_particle = 30;
	particle_settings.out_type = 1;
	particle_settings.time_to_last = 4;
	//particle_settings.ac1 = 0;
	//particle_settings.ac2 = 360;
	
	contents = contentID;
	GF::CheckTile_OverLap(x, y);
	Light_MOTHER::SetColorAndLighting(color, x, y);
	SavedParameters = { ID,x_pos,y_pos,contentID };
	sprite.setColor(color);
	sprite *= spr[0];
	Chests.push_back(this);
	//Putting the object that was just created into a static vector to be used later.
	ColTiles.push_back(this);
}


bool Chest::ifCollisionBefore(bool isPlayer) {
	
	if (isOpen == false && isPlayer == true && sprite.get_is_Active() == true) {
		sprite *= spr[1];
		Player::PlayerObjects[0]->giveItem(contents);
		
		Sound::Play(21, x, y, random2::randomrange(1,5), 0, 0);
		isOpen = true;
		
	}
	return true;
}

void Chest::update() {
	
	for (unsigned int i = 0; i < Chests.size(); i++) {
		if (Chests[i]->Switch >= 0) {
			if (P_Switch_MAIN::Switches[Chests[i]->Switch] == true) {
				if (Chests[i]->sprite.get_is_Active() == false) {
					ParticleSystem::create(Chests[i]->particle_settings);
					Chests[i]->sprite.activate();
				}

			}
		}
		
	}
	
}

Chest::~Chest() {
	for (unsigned int i = 0; i < Chests.size(); i++) {
		if (Chests[i] == this) {
			Chests.erase(Chests.begin() + i);
			break;
		}
	}
}

bool Chest::CheckCollision_Over(int Your_xpos, int Your_ypos) {
	if (x == Your_xpos && y == Your_ypos && sprite.get_is_Active() == true) {
		return true;
	}
	else {
		return false;
	}
}