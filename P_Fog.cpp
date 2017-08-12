#include "stdafx.h"
#include "P_Fog.h"
#include "GF.h"
#include <iostream>
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=CONTROL PANEL-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define setupColor sf::Color::Cyan //This is the color that is used for the block that shows up when the editor is turned on.
#define information_text "P_Fog" //This is the text that appears next to the block to show you information about the block.
#define TypeID 13 //This is the identification of what object it is in relation to others in the NPC_MOTHER class.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

P_Fog::P_Fog(int Type, int x_pos, int y_pos, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	type = Type;
	GF::CheckTile_OverLap(x_pos, y_pos);
	typeID = TypeID;
	SavedParameters = { Type, x_pos, y_pos };
	setup(setupColor, x, y, information_text);
	tex_coords = All_Sprites[TM.getTextureID()][TypeID][0];
	c_ticks = max_c_ticks / random2::randomrange(1, 20);
	for (unsigned int i = 0; i < parts_left_create; i++) {
		particles.push_back(new part(0, (x - 16) + random2::randomrange(1, 48), (y - 16) + random2::randomrange(1, 48), tex_coords, i));
		particles[i]->tick();
	}
	NonCol_InvisibleObjects.push_back(this);
}

P_Fog::~P_Fog() {
	for (unsigned int i = 0; i < particles.size(); i++) {
		delete particles[i];
	}
	particles.clear();
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-~MAIN TICK~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//This function is an overwritten virtual function, but this is a very important function
//So, this is placed seperate from the less important ones.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void P_Fog::tick() {
	for (unsigned int i = 0; i < particles.size(); i++) {
		particles[i]->tick();
	}
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-~VIRTUAL FUNCTIONS~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//These are functions that overwrite the virtual functions in NPC_MOTHER.
//You may change these functions, but it is not necessary.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//This is called if the player lands on the tile.
void P_Fog::if_landed_on() {

}

