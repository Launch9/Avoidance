#pragma once
#include "Invisible_MOTHER.h"
//Item name: Sub_NPC_Block
//Date made 12/13/2016 1:01:39 AM
//Made by Josh

class Sub_NPC_Block : public Invisible_MOTHER
{
private:
	//These contain all Sub_NPC_Block objects created.
	static std::vector<Sub_NPC_Block *> Sub_NPC_Block::Objects;
	//This tells if the tile is active or not.
	bool isTileActive = true;
	//This is for identification purposes within this class type.
	int type = 0;
	//This is the switch ID assigned to the tile.
	//If this is assigned -1, then it will not ever be deactivated.
	int SwitchID = 0;
	//This is called everytime the switches change in the P_Switch_MAIN class.
	void update();
	//This deactivates the tile. (Sub_NPCs can walk through).
	void deactivate_tile();
	//This activates the tile. (Sub_NPCs cannot walk through).
	void activate_tile();
	//Virtual functions {

	//This is called if the player lands on the tile.
	void if_landed_on();
	//This is called every frame.
	void tick();
	//This checks to see if there is anything wanting to know its position is equal or not to another position.
	bool checkCollision_over(int x_pos, int y_pos, bool isPlayer, bool isProjectile);
	//This is called when the world is reset.
	void WorldReset();

	//}

public:
	/*insert constructor description here.*/
	Sub_NPC_Block(int Type, int x_pos, int y_pos, int Switch);
	//Deconstructor
	~Sub_NPC_Block();
	//This updates all the tiles.
	static void update_all();
};

