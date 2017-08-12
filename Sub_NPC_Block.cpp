#include "stdafx.h"
#include "Sub_NPC_Block.h"
#include "GF.h"
#include "Sub_NPC_A.h"
#include "Player.h"
#include "P_Switch_MAIN.h"
std::vector<Sub_NPC_Block *> Sub_NPC_Block::Objects;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=CONTROL PANEL-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define setupColor sf::Color::Red //This is the color that is used for the block that shows up when the editor is turned on.
#define information_text "NPC_Block" //This is the text that appears next to the block to show you information about the block.
#define TypeID 11 //This is the identification of what object it is in relation to others in the NPC_MOTHER class.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Sub_NPC_Block::Sub_NPC_Block(int Type, int x_pos, int y_pos, int Switch)
{
	x = x_pos;
	y = y_pos;
	type = Type;
	GF::CheckTile_OverLap(x_pos, y_pos);
	typeID = TypeID;
	SwitchID = Switch;
	SavedParameters = { Type, x_pos, y_pos, Switch };
	
	setup(setupColor, x, y,  "NPC_Block\nSwitchID: " + GF::str(SwitchID));
	Objects.push_back(this);
	Col_InvisibleObjects.push_back(this);
}

Sub_NPC_Block::~Sub_NPC_Block() {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		if (Objects[i] == this) {
			Objects.erase(Objects.begin() + i);
			break;
		}
	}
}

void Sub_NPC_Block::update() {
	if (SwitchID != -1) {
		if (P_Switch_MAIN::Switches[SwitchID] == true) {
			deactivate_tile();
		}
	}

}

void Sub_NPC_Block::deactivate_tile() {

	isTileActive = false;
}

void Sub_NPC_Block::activate_tile() {
	isTileActive = true;
}

void Sub_NPC_Block::update_all() {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		Objects[i]->update();
	}
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-~MAIN TICK~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//This function is an overwritten virtual function, but this is a very important function
//So, this is placed seperate from the less important ones.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void Sub_NPC_Block::tick() {

}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-~VIRTUAL FUNCTIONS~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//These are functions that overwrite the virtual functions in NPC_MOTHER.
//You may change these functions, but it is not necessary.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//This is called if the player lands on the tile.
void Sub_NPC_Block::if_landed_on() {

}

bool Sub_NPC_Block::checkCollision_over(int x_pos, int y_pos, bool isPlayer, bool isProjectile) {
	if (isTileActive == true) {
		if (isPlayer == false && isProjectile == false) {
			for (unsigned int i = 0; i < Sub_NPC_A::Object_Cache.size(); i++) {
				if (x_pos == x && y_pos == y) {
					return true;
				}
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void Sub_NPC_Block::WorldReset() {
	
	activate_tile();
}