#pragma once
#include "Invisible_MOTHER.h"


class IM_temp : public Invisible_MOTHER
{
private:
	//This is for identification purposes within this class type.
	int type = 0;

	//Virtual functions {

	//This is called if the player lands on the tile.
	void if_landed_on();
	//This is called every frame.
	void tick();

	//}
public:
	/*insert constructor description here.*/
	IM_temp(int Type, int x_pos, int y_pos);
	
};

