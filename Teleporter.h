#pragma once
#include "Invisible_MOTHER.h"
class Teleporter : public Invisible_MOTHER
{
private:
	//This is the floor you want to go to by stepping on this teleporter.
	int floor = 0;
	//This is the dungeon you want to go to by stepping on this teleporter.
	int dungeon = 0;
	//This is the ID of the exit that you walk out of when teleporting.
	int exitID = -1;
	//This is the type of teleporter you are using.
	int Type = 0;
public:
	void tick();
	Teleporter(int type, int x_pos, int y_pos, int Dungeon, int Floor, int ExitID);
	void if_landed_on();
};

