#pragma once
#include "Sub_NPC_A.h"
#include "Sub_NPC_CD.h"
//Item name: EBM
//Date made 12/3/2016 6:09:57 PM
//Made by Josh

class EBM : public Sub_NPC_A, public Sub_NPC_CD
{
private:
	//This is for type identification  within this class. Not the mother class.
	int type = 0;
	//This is a toggle that tells if the eyeball is open or closed.
	bool isOpen = true;
	//This tells if it is doing an animation that, once over, will stop.
	//If = to -1, then it won't do an animation.
	//If = to 2, then it will close eye.
	//If = to 3, then it will open eye.
	int do_ani_type = -1;
	//Tells if it should be setting the animation for standing still.
	//If it has already set it before moving again, then it won't keep setting it.
	bool standing_toggle = false;
	//This does an animation.
	//2 = closing eye
	//3 = opening eye
	void do_ani(int type);
	//This checks to see if it should open or close it's eye.
	void check();
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
	//This overwrites the animation function.
	void animate();
	//This is called once when the class has completed its movement and is waiting for more commands.
	void next();

	//}

public:
	/*insert constructor description here.*/
	EBM(int Type, int x_pos, int y_pos, TileMap &TM);
	
};

