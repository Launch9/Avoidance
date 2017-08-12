#include "stdafx.h"
#include "IM_temp.h"
#include "GF.h"

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=CONTROL PANEL-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define setupColor sf::Color::Cyan //This is the color that is used for the block that shows up when the editor is turned on.
#define information_text "left empty" //This is the text that appears next to the block to show you information about the block.
#define TypeID -1 //This is the identification of what object it is in relation to others in the NPC_MOTHER class.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

IM_temp::IM_temp(int Type, int x_pos, int y_pos)
{
	x = x_pos;
	y = y_pos;
	type = Type;
	GF::CheckTile_OverLap(x_pos, y_pos);
	typeID = TypeID;
	SavedParameters = { Type, x_pos, y_pos };
	setup(setupColor, x, y, information_text);

//	/*type of vector to put the object in.*/.push_back(this);
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-~MAIN TICK~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//This function is an overwritten virtual function, but this is a very important function
//So, this is placed seperate from the less important ones.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void IM_temp::tick() {

}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-~VIRTUAL FUNCTIONS~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//These are functions that overwrite the virtual functions in NPC_MOTHER.
//You may change these functions, but it is not necessary.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//This is called if the player lands on the tile.
void IM_temp::if_landed_on() {

}

