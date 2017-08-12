#pragma once
#include "NPC_MOTHER.h"
#include <functional>
class Laser: public NPC_MOTHER
{
private:
	int dist = 0;
	//Calculated distance in blocks.
	int calcdist = 0;
	//Opposite calculated distance in blocks.
	int opcalcdist = 0;
	//This tells the computer how fast the laser is. In pixels!
	int speed = 0;
	//This tells something? I don't know why it works but I have to use it or the collision detection is all wacky.
	//This is equal to 16 if the laser is horizontal and it equals 0 if vertical.
	int horizontalint = 0;
	//This is pretty much a given...
	int startdirection = -1;
	//This tells the tick function what function to do.
	std::function<void()> lambda;

public:
	//Colors are:
	//0 = normal(greenish yellow), 1 = red, 2 = green, 3 = blue.
	//By default, it will move up and down.
	Laser(int startx, int starty, int startingdirection, TileMap &TM, int distance = 2, int color = 0, int movementspeed = 1);
	void tick(bool render);
	
};