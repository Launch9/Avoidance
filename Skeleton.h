#pragma once
#include "NPC_MOTHER.h"
#include "Sub_NPC_A.h"
#include "Sub_NPC_CD.h"
class Skeleton : public Sub_NPC_A, public Sub_NPC_CD
{
private:
	//This is for the every other moving feature it has.
	bool toggle = false;
	//This is the type of skeleton that it is.
	int type = 0;
	//Tells if it should be setting the animation for standing still.
	//If it has already set it before moving again, then it won't keep setting it.
	bool standing_toggle = false;
	//This is called everytime it needs to reset.
	void reset();
public:
	//Basic constructor
	//These NPCs will move every other turn.
	//They can take hits by projectiles and will die.
	Skeleton(int Type, int x_pos, int y_pos, TileMap &TM);
	//This is called if the player has moved a tile.
	void ifPlayerMoved(int speed, int direction, int spaces, float remainder);
	//Called every frame.
	void tick(bool render);
	//This is called when the NPC dies.
	void when_dead();
	//This is called when the NPC gets reivived.
	void when_revive();

};

