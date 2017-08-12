#pragma once
#include "Invisible_MOTHER.h"
class Cloud_Start : public Invisible_MOTHER
{
private:
	//The starters make clouds when you call the active function.
	//Does not spawn clouds on its own.
	static std::vector<Cloud_Start *> Cloud_Start::Clouds_st; //Starter
	//This is how much time has gone by since the tick counter for this object has been reset.
	float ticks = 0;
	//This tells the clouds when to despawn.
	int end_x = 0;
	//This is how fast the clouds should move.
	int C_speed = 0;
	//If true, direction will be right.
	//If false, direction will be left.
	bool direction = false;
public:
	//These only spawn once, when the world has started.
	Cloud_Start(int type, int x_pos, int y_pos, int x_end, int speed);
	~Cloud_Start();
	void tick();
	void active();
	//Calling this function will make all the Cloud_Start spawners puff out a cloud.
	//This should only be called once, when loading up a world.
	static void activate_all();
};

