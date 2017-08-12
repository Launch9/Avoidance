#pragma once
#include "Basic_Tile_MOTHER.h"
#include "TempText.h"
#include "ParticleSettings.h"
class Chest: public Basic_Tile_MOTHER
{
private:
	//These are the settings for the particles that get created when you activate a chest.
	ParticleSettings particle_settings;
	//This is the contentID for the chest.
	int contents = 0;
	//This is the text the shows when you collected something.
	TempText text;
	//This is the switch that needs to be on for the chest to appear.
	int Switch = -1;
	//These are the sprites that it is going to use.
	std::vector<AniT> spr;
	//This tells the computer wether or not the chest is open.
	bool isOpen = false;
	bool CheckCollision_Over(int Your_xpos, int Your_ypos);
	//This is a vector full of pointers to the objects that were created.
	//This is looped through in the update function to make sure that the ones set to the switch that was just activated turns visible.
	static std::vector<Chest *> Chest::Chests;
public:
	Chest(int ID, int x_pos, int y_pos, int contentID, TileMap &TM);
	~Chest();
	bool ifCollisionBefore(bool isPlayer);
	//This checks all the chests to see if any of them need to be visible now.
	static void update();
};

