#pragma once
#include "Invisible_MOTHER.h"
class Exit : public Invisible_MOTHER
{
private:
	int type = 0;
	int exitID = 0;
	static std::vector<Exit *> Exit::Exits;
public:
	//These tell where the player should spawn when loading up a world.
	//Given the ID, it will tell which Exit to spawn you at when entering a teleporter, or just loading up the world.
	Exit(int Type, int x_pos, int y_pos, int ID);
	//This is for deleting things.
	~Exit();
	void tick();
	//This will loop through all the exits and teleporter the player to the one with the ID given.
	static void teleport_to_exit(int ID);
};

