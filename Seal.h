#pragma once
#include "Basic_Tile_MOTHER.h"
class Seal : public Basic_Tile_MOTHER
{
private:
	//These are the channels that need to be on in order for the seal to open.
	std::vector<int> channels;
	//This boolean tells the seal if it is open or not.
	bool isOpen = false;
	//This is the direction that the seal will move once opened.
	int dir = 0;
	//Opens the seal.
	void open();
	//Closes the seal.
	void close();
	//Checks to see what switches are active in the P_Switch class.
	void update();
	//This is the type of squisher that it is.
	int type = 0;
	//Full of seal pointers the point to the object that resides mainly in the Basic_Tile_MOTHER class.
	static std::vector<Seal *> Seal::Seals;
public:
	//The switchs vector is supposed to be full of indexes of the different switch channels you want.
	Seal(int Type, int x_pos, int y_pos, int Direction, const std::vector<int> &Switches, TileMap &TM);
	//Deconstructor that deletes the pointer in the Seals vector.
	~Seal();
	//This updates all the Seal objects in the Seals class.
	static void update_all();
};

