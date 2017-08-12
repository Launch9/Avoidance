#include "stdafx.h"
#include "SoundBlock.h"
#include "Sound.h"
#include <iostream>
#include "random2.h"
void SoundBlock::SetSound_Pos() {
	for (unsigned int i = 0; i < Sounds.size(); i++) {
		Sounds[i].setPosition(float(x), 0, float(y));
		Sounds[i].setAttenuation(0.03);
	}
}
SoundBlock::SoundBlock(int x_pos, int y_pos, int required_ticks, std::vector<int> ListofSoundIDs)
{
	typeID = 0;
	if (required_ticks <= -1) {
		isReqTick = false;
	}
	else {
		isReqTick = true;
		Reqticks = required_ticks;
	}
	SIndex = 0;
	x = x_pos;
	y = y_pos;
	GF::CheckTile_OverLap(x, y);
	SavedParameters = { x_pos, y_pos, required_ticks };
	//Making all the sound objects.
	for (unsigned int i = 0; i < ListofSoundIDs.size(); i++) {
		SavedParameters.push_back(ListofSoundIDs[i]);
		sf::Sound s;
		s.setBuffer(Sound::GetSoundBuffer(ListofSoundIDs[i]));
		
		Sounds.push_back(s);
	}
	
	setup(sf::Color::Red, x, y, "SoundBlock");
	
	NonCol_InvisibleObjects.push_back(this);
}


void SoundBlock::tick() {
	
	if (isReqTick == true) {
		ticks++;
		if (ticks >= Reqticks) {
			ticks = 0;
			SetSound_Pos();
			if (Sounds.size() >= 1) {
				Sounds[random2::randomrange(0, Sounds.size())].play();
			}
			
		}
			
	}
	else {
		if (Sounds[SIndex].getStatus() != 2) {
			SetSound_Pos();
			Sounds[SIndex].play();
			if (Sounds.size() >= 1) {
				SIndex = random2::randomrange(0, Sounds.size());
			}
		}
	}
	
}