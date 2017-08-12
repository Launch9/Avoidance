#pragma once
#include "Invisible_MOTHER.h"
//Item name: IPTile
//Date made 12/14/2016 12:10:33 AM
//Made by Josh

class IPTile : public Invisible_MOTHER
{
private:
	//This is for identification purposes within this class type.
	int type = 0;
	//This is the ID of the switch that it triggers.
	int SwitchID = 0;
	//This tells if you have landed on the tile yet.
	bool has_landed = false;
	//Virtual functions {

	//This is called if the player lands on the tile.
	void if_landed_on();
	//This is called every frame.
	void tick();
	//This is called when the world is reset.
	void WorldReset();
	//}
public:
	/*insert constructor description here.*/
	IPTile(int Type, int x_pos, int y_pos, int Switch);
	
};

