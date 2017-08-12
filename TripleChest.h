#pragma once
#include "Basic_Tile_MOTHER.h"
///This is a class that allows you to make a chest that takes two taps to get. Uses three sprites(triple).
///It can be inherited from and will allow you to overwrite the if_open virtual function to make a action happen when one opens.
class TripleChest : public Basic_Tile_MOTHER
{
private:
	//This tells how many times you have tried to open it.
	int howManyTimes = 0;
	//This is the switchID and it will activate a switch once opened completely.
	int switchID = -1;
	//This is the max amount of times that it takes to open the chest.
	int max_times = 2;
	//This is the ID of the content.
	int content = 0;
	//This tells if the chest is open or not.
	bool is_open = false;
public:
	TripleChest(int type, int x_pos, int y_pos, int contentID, int SwitchID, TileMap &TM);
	bool ifCollisionBefore(bool isPlayer);
};

