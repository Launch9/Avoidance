#pragma once
#include "Basic_Tile_MOTHER.h"
#include "P_Switch.h"
#include <functional>
class P_Spawner_Const : public Basic_Tile_MOTHER
{
private:
	//This is how many ticks it has to count up to until it fires again.
	float max_ticks_til_shot = 0;
	//This is how many ticks have gone by for the firing counter.
	float Fcounter = 0;
	//This is the type of projectile that shoots out.
	int type_of_projectile = 0;
	//This is the channel for which switch must be on in order for it to fire.
	int channel = 0;
	//This is for determining which direction it needs to be shot in.
	int dir = 0;

public:
	int getType_of_projectile();
	//If SwitchChannel is left blank, it will shoot as soon as you enter the floor.
	//Otherwise, it will start shooting forever once activated by that switch.
	P_Spawner_Const(const int &type, const int &x_pos, const int &y_pos, const int &Direction, TileMap &TM, const int &SwitchChannel = -1);
	//Overwritting the virtual animate function so that it can check ticks.
	void animate();
	//this is the function that really animates.
	//It also checks to see if its ready to fire or not.
	void real_animate();
};

