#pragma once
#include "Invisible_MOTHER.h"
class Cloud_Spawner : public Invisible_MOTHER
{
private:
	
	
	
	//This is how much time has gone by since the tick counter for this object has been reset.
	float ticks = 0;
	//This is the max number of ticks that need to be reached before the counter is reset.
	int mt = 0;
	//This tells the clouds when to despawn.
	int end_x = 0;
	//This is how fast the clouds should move.
	int C_speed = 0;
	//If true, direction will be right.
	//If false, direction will be left.
	bool direction = false;
public:
	
	Cloud_Spawner(int type, int x_pos, int y_pos, int x_end, int max_ticks, int speed);
	void tick();
};

