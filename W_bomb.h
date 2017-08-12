#pragma once
#include "Sub_NPC_A.h"
#include "Sub_NPC_CD.h"
#include "TileMap.h"
//Item name: W_bomb
//Date made 11/27/2016 7:10:42 PM
//Made by Josh

class W_bomb : public Sub_NPC_A, public Sub_NPC_CD
{
private:
	//This makes sure the bomb moves every other turn.
	bool toggle = true;
	//This is for type identification  within this class. Not the mother class.
	int type = 0;
	//This is a pointer to the Tilemap. Held in the header file for use when the NPC dies.
	//Use for making the blast.
	TileMap *tmap;
	//Tells if it should be setting the animation for standing still.
	//If it has already set it before moving again, then it won't keep setting it.
	bool standing_toggle = false;

	//Virtual functions{

	//This is called if the player has moved a tile.
	void ifPlayerMoved(int speed, int direction, int spaces, float remainder);
	//Called every frame.
	void tick(bool render);
	//This function is called when the NPC is revived.
	void when_revive();
	//This function is called when the NPC is killed or deleted_self.
	void when_dead();
	//This is called when the player dies, the editor starts, etc.
	//Its purpose is to place everything back to where it started.
	void reset();
	//This is called once when the class has completed its movement and is waiting for more commands.
	void next();

	//}

public:
	/*insert constructor description here.*/
	W_bomb(int Type, int x_pos, int y_pos, TileMap &TM);
	
};

