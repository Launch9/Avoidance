#pragma once
#include "NPC_MOTHER.h"
#include "RT.h"
//Item name: Big_Squisher
//Date made 12/16/2016 1:13:12 AM
//Made by Josh

class Big_Squisher : public NPC_MOTHER
{
private:
	//These are the blocks that are part of the squisher.
	std::vector<ST *> blocks;
	//This tells to play a sound every other movement.
	bool stoggle = 0;
	//This integer does the calculation of distance + back_add etc, while it is being created.
	float db = 0;
	//This is the size of the block.
	sf::Vector2f s;
	//These are added to the direction that you may be going.
	//Modified when created.
	std::vector<int> add_ons = { 0,0,0,0 };
	//This is the original direction that you wanted it to go in.
	int origin_direction = 0;
	//This tells if the squisher is waiting for the command to tell it to move.
	bool isWaiting = true;
	//This is the type of Big_Squisher it is.
	int type = 0;
	//This is the distance that is goes.
	int distance = 5;
	//This is the direction.
	int direction = 0;
	//This is the speed at which the squisher moves.
	int speed = 5;
	//This keeps count of how long it has been waiting.
	float how_long = 0;
	//This is how long it waits when it is retracted.
	float max_time = 3;
	//Number of times squished.
	int num_SQ = 0;
	//This is the max number of times is squishes before going into rest.
	int max_num_SQ = 1;
	//Virtual functions{
	void animate();
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

	
	Big_Squisher(int type, int x_pos, int y_pos, int Distance, int Direction, TileMap &TM);
	
	~Big_Squisher();
	
	

	

};

