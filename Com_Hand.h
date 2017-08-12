#pragma once
#include "NPC_MOTHER.h"
#include "DText.h"
//Item name: Com_Hand
//Date made 12/28/2016 1:53:38 AM
//Made by Josh

class Com_Hand : public NPC_MOTHER
{
private:
	//This is the switch channel that turns true when the enemy dies.
	int channel = 0;
	//This is the distance that the hand launches.
	int LaunchDistance = 32 * 10;
	//This integer tells what is happening to the hand at the moment.
	int currentEvent = 0;
	//This is how many ticks have gone by while it is waiting for retraction.
	float WTicks = 0;
	//This is how many ticks are needed until it stops waiting.
	float max_WTicks = 5;
	//Number of hits needed.
	float max_hits = 50;
	//Total number of hits so far.
	float hits = 0;
	//This is damage text for the block.
	DText damage_text_block;
	//This is how many ticks have gone by since it has been fired.
	float LTicks = 0;
	//This is how many ticks are required untill stopping.
	float max_LTicks = 0.5;
	//This is the degree at which the player is relative to the 
	float degree = 0;
	//This is the distance that the hand is from the spawn point.
	float distance = 0;
	//This tells if the hand should point toward the player.
	bool should_point = true;
	//This is the sprite of the chain.
	CT chain;
	//This contains the animation for the claw when it is not blinking.
	std::vector<AniT> no_blink_ani;
	//This contains the animation for the claw when it is blinking.
	std::vector<AniT> blink_ani;
	//This is the type of Com_Hand it is.
	int type = 0;
	//This is called whenever the init block is damaged.
	void damageBlock(Projectile &P);
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

	
	Com_Hand(int type, int x_pos, int y_pos, int Switchchannel, TileMap &TM);
	
	
	
	

	

};

