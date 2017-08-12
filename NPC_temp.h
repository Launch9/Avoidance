#pragma once
#include "NPC_MOTHER.h"
//Item name: $itemname$
//Date made $time$
//Made by $username$

class NPC_temp : public NPC_MOTHER
{
private:
	//This is the type of $safeitemname$ it is.
	int type = 0;

	//Virtual functions{

	//This function is called when the NPC is revived.
	void when_revive();
	//This function is called when the NPC is killed or deleted_self.
	void when_dead();
	//This is called when the player dies, the editor starts, etc.
	//Its purpose is to place everything back to where it started.
	void reset();
	//This is the tick function that is overwritten.
	//This is called every frame.
	void tick(bool render);

	//} ~Virtual functions
public:

	
	NPC_temp(int type, int x_pos, int y_pos, TileMap &TM);
	
	
	
	

	

};

