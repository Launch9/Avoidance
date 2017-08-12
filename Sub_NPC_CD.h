#pragma once
#include <vector>
///This class tells the system that the NPC that is inheriting this class needs to be killed in order to progress.
class Sub_NPC_CD
{
private:
	//This tells how many are dead.
	static unsigned int Sub_NPC_CD::HowManyDead;
	//This tells to see if the NPC is dead or not.
	bool is_dead = false;
	//This is a vector that holds all the pointers to the objects that were created by classes that inherited this class.
	static std::vector<Sub_NPC_CD *> Sub_NPC_CD::Objects;
public:
	Sub_NPC_CD();
	~Sub_NPC_CD();
	//This should be called when the NPC dies, so that the class can keep track of what is dead and what is not.
	void call_when_dead();
	//This is called when you want to loop through all the objects that are contained in this class and check to see if the deathSwitch in the P_Main class should be true.
	static void check();
	//This initializes everything.
	static void init();
};

