#pragma once
#include "Invisible_MOTHER.h"
#include <SFML/Audio.hpp>
class SoundBlock: public Invisible_MOTHER
{
private:
	/*This variable determines what sound index it is working on.
	This is only used if you do not have any required ticks.*/
	int SIndex = 0;
	//This is the variable for determining how many ticks have gone by.
	int ticks = 0;
	//This is the boolean that determines wether or not you gave a proper amount of required ticks.
	bool isReqTick = false;
	//This is the required ticks that need to pass before it plays its sounds again.
	int Reqticks = 0;
	//These are the sounds that are played at the given tick.
	std::vector<sf::Sound> Sounds;
	//This function sets the sound position of all the sounds in the block.
	void SetSound_Pos();
	

public:
	
	//This constructor is used if you want to make an object that plays multiple sounds in a random order.
	//If the required_ticks is given a number less then 0, it will just play the sound over once it is done.
	SoundBlock(int x_pos, int y_pos, int required_ticks, std::vector<int> ListofSoundIDs);
	//Overwritten function.
	void tick(); 
};

