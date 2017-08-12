#include "stdafx.h"
#include "IPTile.h"
#include "GF.h"
#include "P_Switch_MAIN.h"
#include <iostream>
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=CONTROL PANEL-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define setupColor sf::Color::Green //This is the color that is used for the block that shows up when the editor is turned on.
#define information_text "" //This is the text that appears next to the block to show you information about the block.
#define TypeID 12 //This is the identification of what object it is in relation to others in the NPC_MOTHER class.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

IPTile::IPTile(int Type, int x_pos, int y_pos, int Switch)
{
	x = x_pos;
	y = y_pos;
	type = Type;
	GF::CheckTile_OverLap(x_pos, y_pos);
	typeID = TypeID;
	SwitchID = Switch;
	SavedParameters = { Type, x_pos, y_pos, Switch };
	setup(setupColor, x, y, "IPTile\nSwitchID: " + GF::str(SwitchID));
	
	NonCol_InvisibleObjects.push_back(this);
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-~MAIN TICK~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//This function is an overwritten virtual function, but this is a very important function
//So, this is placed seperate from the less important ones.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void IPTile::tick() {

}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-~VIRTUAL FUNCTIONS~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//These are functions that overwrite the virtual functions in NPC_MOTHER.
//You may change these functions, but it is not necessary.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//This is called if the player lands on the tile.
void IPTile::if_landed_on() {
	if (has_landed == false) {
		P_Switch_MAIN::Switches[SwitchID] = true;
		P_Switch_MAIN::update();
		has_landed = true;
	}
}

void IPTile::WorldReset() {
	has_landed = false;
	P_Switch_MAIN::Switches[SwitchID] = false;
	P_Switch_MAIN::update();
}