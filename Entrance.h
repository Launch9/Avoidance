#pragma once
#include "Invisible_MOTHER.h"
class Entrance : public Invisible_MOTHER
{
private:
	int type = 0;
	int roomIDenter = 0;
	int roomIDexit = 0;
public:
	Entrance(int Type, int x_pos, int y_pos, int RoomIDenter, int RoomIDexit);
	void tick();
	//This is called when the player lands on the x and y cordiantes.
	void if_landed_on();
};

