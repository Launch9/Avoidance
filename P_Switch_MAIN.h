#pragma once
#include <vector>
class P_Switch_MAIN
{
public:
	//This is true if all the enemies in a room have been defeated all in one life.
	static bool P_Switch_MAIN::deathSwitch;
	//These are the switches that are used when determining if two or more things are active in a world.
	static std::vector<bool> P_Switch_MAIN::Switches;
	//This sets all switch channels to false.
	//You have to do this before using this class.
	//I put this function call into the init function of the World.cpp file. init(), loadworld()
	static void clearSwitches();
	
	//This initiates the switches.
	//This does the same thing as clearSwitches does.
	//But this is just for making sure that you get the idea of it.
	static void init();
	//This will update all the things that need to be updated when a switch changes.
	static void update();
};

